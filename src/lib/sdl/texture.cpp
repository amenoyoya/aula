#include <aula/sdl/application.hpp>

namespace Aula {
    namespace SDL {
        bool Texture::open(u32 width, u32 height, u8 type) {
            SDL_Renderer *r = getRendererHandle();
            if (!r) {
                _message = "failed to create texture: unknown renderer";
                _state = Object::State::FAILED;
                return false;
            }
            close();
            if (nullptr == (texture = SDL_CreateTexture(
                r,
                SDL_PIXELFORMAT_ARGB8888,
                type,
                size.width = width,
                size.height = height
            ))) {
                _message = "failed to create texture";
                _state = Object::State::FAILED;
                return false;
            }
            if (!setBlendMode(BLEND_ALPHA)) {
                _message = "failed to create texture: cannot set blend mode";
                _state = Object::State::FAILED;
                return false;
            }
            _state = Object::State::ACTIVE;
            return true;
        }

        bool Texture::openFromImage(const IO::Binary &data, const Color *colorKey) {
            SDL_Surface *surface = nullptr;
            if (nullptr == (surface = IMG_Load_RW(SDL_RWFromMem((void*)data.getPointer(), data.getSize()), 1))) {
                _message = "failed to call IMG_Load_RW";
                _state = Object::State::FAILED;
                return false;
            }
            if (colorKey) {
                SDL_SetColorKey(surface, SDL_RLEACCEL, SDL_MapRGB(surface->format, colorKey->red, colorKey->green, colorKey->blue));
            }
            
            bool result = openFromSurface(surface);
            SDL_FreeSurface(surface);
            return result;
        }

        bool Texture::openFromColorData(u32 width, u32 height, const IO::Binary &colordata, bool isAlpha) {
            SDL_Surface *surface = nullptr;
            if (colordata.getSize() < width * height * (isAlpha? 4: 3)) {
                _message = "failed to create texture: not enough color data size";
                _state = Object::State::FAILED;
                return false;
            }
            if (nullptr == (surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, isAlpha? 32: 24,
                #if SDL_BYTEORDER == SDL_LIL_ENDIAN
                    0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
                #else
                    0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
                #endif
            ))) {
                _message = "failed to call SDL_CreateRGBSurface";
                _state = Object::State::FAILED;
                return false;
            }
            SDL_LockSurface(surface);
            memcpy((u8*)surface->pixels, (u8*)colordata.getPointer(), width * height * (isAlpha? 4: 3));
            SDL_UnlockSurface(surface);

            bool result = openFromSurface(surface);
            SDL_FreeSurface(surface);
            return result;
        }

        bool Texture::openFromText(const Font &font, const std::string &text) {
            if (font.getHandle() == nullptr) {
                _message = "failed to create texture: font is null";
                _state = Object::State::FAILED;
                return false;
            }

            SDL_Color color = {255, 255, 255, 255};
            SDL_Surface *surface = TTF_RenderUTF8_Blended((TTF_Font *)font.getHandle(), text.c_str(), color);
            if (surface == nullptr) {
                _message = "failed to call TTF_RenderUTF8_Blended";
                _state = Object::State::FAILED;
                return false;
            }

            bool result = openFromSurface(surface);
            SDL_FreeSurface(surface);
            return result;
        }
        
        void Texture::close(){
            if (data) {
                free(data);
                data = nullptr;
            }
            if (texture) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
            _message.clear();
            _state = Object::State::NONE;
        }
        
        bool Texture::draw(i32 x, i32 y, i32 w, i32 h, i32 sx, i32 sy, i32 sw, i32 sh) {
            SDL_Renderer *r = getRendererHandle();
            SDL_Rect src = { sx, sy, sw == -1 ? size.width : sw, sh == -1 ? size.height : sh },
                dest = { x, y, w == -1? size.width : w, h == -1 ? size.height : h };
            SDL_Point cp = { center.x == -1 ? size.width / 2 : center.x, center.y == -1 ? size.height / 2 : center.y };
            return r ? (0 == SDL_RenderCopyEx(r, texture, &src, &dest, angle, &cp, (SDL_RendererFlip)flip)) : false;
        }

        bool Texture::openFromSurface(SDL_Surface *surf) {
            SDL_Renderer *r = getRendererHandle();
            if (!r) {
                _message = "failed to create texture: unknown renderer";
                _state = Object::State::FAILED;
                return false;
            }
            if (!surf) {
                _message = "failed to create texture: surface is null";
                _state = Object::State::FAILED;
                return false;
            }
            close();

            SDL_RendererInfo info;
            const SDL_PixelFormat *fmt;
            bool needAlpha = false;
            u32 f = 0;
            
            SDL_GetRendererInfo(r, &info);
            /* See what the best texture format is */
            fmt = surf->format;
            if (fmt->Amask || SDL_GetColorKey(surf, nullptr) == 0) needAlpha = true;
            f = info.texture_formats[0];
            for (u32 i = 0; i < info.num_texture_formats; ++i) {
                if (!SDL_ISPIXELFORMAT_FOURCC(info.texture_formats[i]) && SDL_ISPIXELFORMAT_ALPHA(info.texture_formats[i]) == needAlpha) {
                    f = info.texture_formats[i];
                    break;
                }
            }
            if (nullptr == (texture = SDL_CreateTexture(
                r,
                f,
                SDL_TEXTUREACCESS_STATIC,
                size.width = surf->w,
                size.height = surf->h
            ))) {
                _message = "failed to create texture";
                _state = Object::State::FAILED;
                return false;
            }
            if (f == surf->format->format) {
                if (SDL_MUSTLOCK(surf)) {
                    SDL_LockSurface(surf);
                    SDL_UpdateTexture(texture, nullptr, surf->pixels, surf->pitch);
                    SDL_UnlockSurface(surf);
                } else {
                    SDL_UpdateTexture(texture, nullptr, surf->pixels, surf->pitch);
                }
                // オリジナルピクセルデータを保持
                format = surf->format->BytesPerPixel;
                data = (u8*)malloc(surf->pitch * surf->h);
                memcpy(data, surf->pixels, surf->pitch * surf->h);
            } else {
                SDL_PixelFormat *dst_fmt = SDL_AllocFormat(f);
                SDL_Surface *temp = SDL_ConvertSurface(surf, dst_fmt, 0);
                /* Set up a destination surface for the texture update */
                SDL_FreeFormat(dst_fmt);
                if (temp) {
                    SDL_UpdateTexture(texture, nullptr, temp->pixels, temp->pitch);
                    // オリジナルピクセルデータを保持
                    format = temp->format->BytesPerPixel;
                    data = (u8*)malloc(temp->pitch * temp->h);
                    memcpy(data, temp->pixels, temp->pitch * temp->h);
                    SDL_FreeSurface(temp);
                } else {
                    close();
                    _message = "failed to create texture: cannot update pixel data";
                    _state = Object::State::FAILED;
                    return false;
                }
            }
            /* カラーキーなどの処理 */
            u8 R, G, B, A;
            SDL_BlendMode blendMode;
            
            SDL_GetSurfaceColorMod(surf, &R, &G, &B);
            setColor(R, G, B);
            SDL_GetSurfaceAlphaMod(surf, &A);
            setAlpha(A);
            if (SDL_GetColorKey(surf, nullptr) == 0) {
                /* We converted to a texture with alpha format */
                if (!setBlendMode(BLEND_ALPHA)) {
                    _message = "failed to create texture: cannot set blend mode";
                    _state = Object::State::FAILED;
                    return false;
                }
            } else {
                SDL_GetSurfaceBlendMode(surf, &blendMode);
                if (!setBlendMode((u8)blendMode)) {
                    _message = "failed to create texture: cannot set blend mode";
                    _state = Object::State::FAILED;
                    return false;
                }
            }
            _state = Object::State::ACTIVE;
            return true;
        }
    }
}
