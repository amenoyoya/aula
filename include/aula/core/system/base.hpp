#pragma once

#include <aula/core/path/base.hpp>

namespace Aula {
    /// システム関連
    namespace System {
        /// コマンドライン引数を UTF-8 に変換して取得
        // @param argv: wchar_t* or char*[] コマンドライン引数
        // @pram argc: コマンドライン引数の数
        template<typename Char>
        inline std::vector<std::string> getUTF8CommandLineArguments(Char *argv[], u32 argc) {
            std::vector<std::string> arguments;

            for (u32 i = 0; i < argc; ++i) {
                if (i == 0) {
                    // Current execution file: => Get full path
                    arguments.push_back(Path::complete(Encoding::toUTF8(argv[i])));
                    continue;
                }
                arguments.push_back(Encoding::toUTF8(argv[i]));
            }
            return std::move(arguments);
        }

        /// コマンド実行
        inline i32 execute(const std::string &cmd) {
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
        inline bool setEnvironmentVariable(const std::string &name, const std::string &val) {
            #ifdef _WINDOWS
                return FALSE != SetEnvironmentVariableW(Encoding::utf8ToWideString(name).c_str(), Encoding::utf8ToWideString(val).c_str());
            #else
                return 0 == putenv((char*)(name + "=" + val).c_str());
            #endif
        }
        
        /// 環境変数取得
        std::string getEnvironmentVariable(const std::string &name);
        
        
        /* 作業ディレクトリ */
        /// 作業ディレクトリ変更
        inline bool setCurrentDirectory(const std::string &dir) {
            #ifdef _WINDOWS
                return FALSE != SetCurrentDirectoryW(Encoding::utf8ToWideString(dir).c_str());
            #else
                return 0 == chdir(dir.c_str());
            #endif
        }
        
        /// 作業ディレクトリ取得
        std::string getCurrentDirectory();
    }
}
