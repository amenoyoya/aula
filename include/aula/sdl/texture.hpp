#pragma once

#include "font.hpp"
#include <SDL_image.h>

namespace Aula {
    namespace SDL {
        /// Texture class
        // * Texture is used in hardware rendering <=> Surface is used in software rendering
        class Texture : public Object {
        public:
            Texture(): Object(), texture(nullptr), angle(0.0), flip(0), format(0), data(nullptr) {}
            explicit Texture(u32 width, u32 height, u8 type = TEXTURE_STREAMING)
                : Object(), texture(nullptr), angle(0.0), flip(0), format(0), data(nullptr)
            {
                open(width, height, type);
            }
            explicit Texture(const IO::Binary &imgdata, const Color *colorKey = nullptr)
                : Object(), texture(nullptr), angle(0.0), flip(0), format(0), data(nullptr)
            {
                openFromImage(imgdata, colorKey);
            }
            explicit Texture(u32 width, u32 height, const IO::Binary &colordata, bool isAlpha = true)
                : Object(), texture(nullptr), angle(0.0), flip(0), format(0), data(nullptr)
            {
                openFromColorData(width, height, colordata, isAlpha);
            }
            explicit Texture(const Font &font, const std::string &text)
                : Object(), texture(nullptr), angle(0.0), flip(0), format(0), data(nullptr)
            {
                openFromText(font, text);
            }
            ~Texture() {
                close();
            }
            
            /// 空テクスチャ作成
            bool open(u32 width, u32 height, u8 type = TEXTURE_STREAMING);

            /// 画像データからテクスチャ作成
            // @param colorKey: 指定した場合、指定色を透明化
            bool openFromImage(const IO::Binary &imgdata, const Color *colorKey = nullptr);

            /// RGBデータからテクスチャ作成
            bool openFromColorData(u32 width, u32 height, const IO::Binary &colordata, bool isAlpha = true);

            /// 文字列からテクスチャ作成
            bool openFromText(const Font &font, const std::string &text);

            /// テクスチャ削除
            void close();

            /// @todo 画像として保存
            /*bool saveToImage(const std::string &filename, u8 type = SAVE_PNG) {
                if (surface == nullptr) return false;
                return type == SAVE_BMP
                    ? 0 == SDL_SaveBMP(surface, filename.c_str())
                    : 0 == IMG_SavePNG(surface, filename.c_str());
            }*/
            
            /// 回転設定
            Texture *setAngle(double _angle) {
                angle = _angle; return this;
            }

            // 中心設定
            // -1を指定すると中心をサイズ/2に
            Texture *setCenter(i32 x, i32 y) {
                center.x = x, center.y = y; return this;
            }
            
            /// 反転設定 (0: 通常、1: 水平反転、2: 垂直反転)
            Texture *setFlip(u8 type = 0) {
                flip = type; return this;
            }
            
            /// ブレンディング設定
            bool setBlendMode(u8 mode = BLEND_ALPHA) {
                return texture ? 0 == SDL_SetTextureBlendMode(texture, (SDL_BlendMode)mode) : false;
            }

            /// 色設定
            bool setColor(u8 r, u8 g, u8 b) {
                return texture ? 0 == SDL_SetTextureColorMod(texture, r, g, b) : false;
            }
            bool setColor(const Color &color) {
                return setColor(color.red, color.green, color.blue) && setAlpha(color.alpha);
            }
            bool setAlpha(u8 a) {
                return texture ? 0 == SDL_SetTextureAlphaMod(texture, a) : false;
            }
            
            /// ピクセルデータ取得
            const u8 &getFormat() const { return format; }
            u8 *getPixels() { return data; }
            
            /// getPixels() のポインタで設定したピクセルデータをテクスチャに反映
            bool updatePixels() {
                return data? 0 == SDL_UpdateTexture(texture, nullptr, data, size.width * format) : false;
            }
            
            /// 描画(w, hに-1を指定すると原寸大)
            bool draw(i32 x, i32 y, i32 w = -1, i32 h = -1, i32 sx = 0, i32 sy = 0, i32 sw = -1, i32 sh = -1);
            
            const SDL_Texture *getHandle() const { return texture; }
            const Size &getSize() const { return size; }
        private:
            SDL_Texture *texture;
            Size         size; // サイズ
            Point        center; // 回転中心
            double       angle; // 角度
            u8           flip; // 反転タイプ
            
            /* ピクセルデータ */
            u8           format; // RGBかRGBAか(3 or 4)
            u8          *data;

            /// Surfaceからテクスチャを作成
            bool openFromSurface(SDL_Surface *surface);
        };
    }
}
