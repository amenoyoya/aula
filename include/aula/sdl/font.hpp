#pragma once

#include "../core.hpp"
#include "types.event.hpp"
#include "types.hpp"

#define UNICODE
#define SDL_MAIN_HANDLED // デスクトップ環境ならSDLのmain関数は使わない

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

namespace Aula {
    namespace SDL {
        /// TTF Font class
        class Font: public Object {
        public:
            Font(): Object(), font(nullptr) {}
            explicit Font(const std::string &fontname, u32 size): Object(), font(nullptr) {
                open(fontname, size);
            }
            ~Font() {
                close();
            }
            
            /// フォント利用開始
            bool open(const std::string &fontname, u32 size) {
                close();
                if (nullptr == (font = TTF_OpenFont(fontname.c_str(), size))) {
                    _message = "failed to open font: " + fontname + " (" + Encoding::toString(size) + "px)";
                    _state = Object::State::FAILED;
                    return false;
                }
                _state = Object::State::ACTIVE;
                return true;
            }
            
            /// フォント利用終了
            void close() {
                if (font) {
                    TTF_CloseFont(font);
                    font = nullptr;
                }
                _message.clear();
                _state = Object::State::NONE;
            }
            
            /// フォントスタイル設定
            void setStyle(u8 style) {
                if (font) TTF_SetFontStyle(font, style);
            }
            
            /// 指定テキストを Surface にしたときのサイズを計算
            Size getTextSize(const std::string &text) const {
                Size size;
                
                if (font) TTF_SizeUTF8(font, text.c_str(), (int*)&size.width, (int*)&size.height);
                return size;
            }
            
            /// フォント縦幅を取得
            u32 getHeight() const {
                return font ? TTF_FontHeight(font) : 0;
            }

            const TTF_Font *getHandle() const { return font; }
        private:
            TTF_Font *font;
        };
    }
}
