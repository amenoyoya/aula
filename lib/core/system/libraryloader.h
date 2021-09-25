#pragma once

#include "../encoding/base.h"

namespace Aula {
    namespace System {
        /// 動的ライブラリ読み込みクラス
        class LibraryLoader: public Object {
            u32 handle;
        public:
            LibraryLoader(): Object(), handle(0) {}
            explicit LibraryLoader(const std::string &path): Object(), handle(0) {
                open(path);
            }
            ~LibraryLoader() {
                close();
            }
            
            /// dllファイルオープン
            bool open(const std::string &path);
            
            /// dllファイルクローズ
            void close();
            
            /// 指定関数名の関数をロード
            void *getFunction(const std::string &name) {
                #ifdef _WINDOWS
                    return handle? (void*)GetProcAddress((HMODULE)handle, name.c_str()): nullptr;
                #else
                    return handle? dlsym((void*)handle, name.c_str()): nullptr;
                #endif
            }
        };
    }
}