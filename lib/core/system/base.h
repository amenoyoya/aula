#pragma once

#include "../encoding/base.h"

namespace Aula {
    /// システム関連
    namespace System {
        /// コマンド実行
        inline i32 execute(const string &cmd) {
            #ifdef _WINDOWS
                #ifdef _MSC_VER
                    return _wsystem(Encoding::utf8ToWideString(cmd).c_str());
                #else
                    return system(Encoding::utf8ToShiftJIS(cmd).c_str());
                #endif
            #else
                return /*WEXITSTATUS(*/system(cmd.c_str())/*)*/;
            #endif
        }
        
        /// スリープ
        inline void sleep(u32 msec) {
            #ifdef _WINDOWS
                Sleep(msec);
            #else
                usleep(msec*1000);
            #endif
        }
        
        /// システム時間を取得(ミリ秒単位)
        u32 getTime();
        

        /* 環境変数 */
        /// 環境変数設定
        inline bool setEnvironmentVariable(const string &name, const string &val) {
            #ifdef _WINDOWS
                return FALSE != SetEnvironmentVariable(Encoding::utf8ToWideString(name).c_str(), Encoding::utf8ToWideString(val).c_str());
            #else
                return 0 == putenv((char*)(name + "=" + val).c_str());
            #endif
        }
        
        /// 環境変数取得
        string getEnvironmentVariable(const string &name);
        
        
        /* 作業ディレクトリ */
        /// 作業ディレクトリ変更
        inline bool setCurrentDirectory(const string &dir) {
            #ifdef _WINDOWS
                return FALSE != SetCurrentDirectory(Encoding::utf8ToWideString(dir).c_str());
            #else
                return 0 == chdir(dir.c_str());
            #endif
        }
        
        /// 作業ディレクトリ取得
        string getCurrentDirectory();
    }
}
