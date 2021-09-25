#pragma once

#include "../encoding/base.h"

namespace Aula {
    /// コンソール制御関連
    namespace Console {
        /// UTF-8文字列標準出力
        inline void writeLine(const string &str) {
            #ifdef _WINDOWS
                wprintf(L"%s\n", Encoding::utf8ToWideString(str).c_str());
            #else
                printf("%s\n", str.c_str());
            #endif
        }
        inline void write(const string &str) {
            #ifdef _WINDOWS
                wprintf(L"%s", Encoding::utf8ToWideString(str).c_str());
            #else
                printf("%s", str.c_str());
            #endif
        }
        
        /// コンソール色
        enum Color {
            BLACK,
            BLUE,
            GREEN,
            CYAN,
            RED,
            PURPLE,
            YELLOW,
            WHITE
        };
        
        /// コンソールテキストの色・属性を設定する
        // 引数 : 前景色, 背景色, 高輝度フラグ, 下線フラグ
        bool setAttribute(i8 wFore=WHITE, i8 wBack=BLACK, bool bHigh=false, bool bUnderscore=false);
        
        /// カーソルの位置をセットする
        bool setCursorPosition(i16 shXPos, i16 shYPos);
        
        /// 画面を消去する
        bool clear();
        
        /// キー入力があるか調べる
        bool isKeyPressed();
        
        /// 入力されたキーコードを取得する
        i32 getPressedKey();
        
        #ifdef _WINDOWS
            /*** Windows専用 ***/
            /// コンソール表示
            void open();
            
            /// コンソール解放
            inline void close() {
                FreeConsole();
            }
        #endif
    }
}
