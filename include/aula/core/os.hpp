#pragma once

#include "path.hpp"
#include <vector>

#ifdef _WINDOWS
    #include <mmsystem.h>
#else
    #include <sys/time.h>
#endif

namespace aula {
    namespace os {
        /// execute os command
        inline long execute(const std::string &cmd) {
            #ifdef _WINDOWS
                return _wsystem(std::move(string::u8towcs(cmd)).c_str());
            #else
                return /*WEXITSTATUS(*/ system(cmd) /*)*/;
            #endif
        }

        /// sleep [milli seconds]
        inline void sleep(unsigned long msec) {
            #ifdef _WINDOWS
                Sleep(msec);
            #else
                usleep(msec * 1000);
            #endif
        }

        /// get current os time [milli seconds]
        inline unsigned long systime() {
            #ifdef _WINDOWS
                return timeGetTime();
            #else
                struct timeval tv;
                gettimeofday(&tv, nullptr);
                return tv.tv_sec * 1000 + tv.tv_usec / 1000;
            #endif
        }

        /// set system environmental value
        inline bool setenv(const std::string &envname, const std::string &val) {
             #ifdef _WINDOWS
                return FALSE != SetEnvironmentVariableW(std::move(string::u8towcs(envname)).c_str(), std::move(string::u8towcs(val)).c_str());
            #else
                return 0 == putenv((char*)(envname + "=" + val).c_str());
            #endif
        }

        /// get system environmental value
        inline std::string getenv(const std::string &envname) {
            #ifdef _WINDOWS
                std::wstring name = std::move(string::u8towcs(envname)), buf;
                size_t size = GetEnvironmentVariable(name.c_str(), nullptr, 0);
                
                if(size == 0) return "";
                buf.resize(size);
                GetEnvironmentVariable(name.c_str(), (wchar_t*)buf.c_str(), size);
                return std::move(string::wcstou8(buf));
            #else
                return getenv(envname.c_str());
            #endif
        }

        /// set current working directory
        inline bool setcwd(const std::string &dir) {
            #ifdef _WINDOWS
                return FALSE != SetCurrentDirectoryW(std::move(string::u8towcs(dir)).c_str());
            #else
                return 0 == chdir(dir.c_str());
            #endif
        }
        
        /// get current working directory
        inline std::string getcwd() {
            #ifdef _WINDOWS
                std::wstring buffer;
                
                buffer.resize(1024);
                GetCurrentDirectory(1024, (wchar_t*)buffer.c_str());
                return std::move(string::wcstou8(buffer.c_str()));
            #else
                char dest[1024];
                return getcwd(dest, 1024);
            #endif
        }

        /// convert command line arguments to std::vector<std::string(UTF-8)>
        template<typename Char>
        std::vector<std::string> cmdline(Char *argv[], int argc) {
            std::vector<std::string> arguments;

            for (int i = 0; i < argc; ++i) {
                if (i == 0) {
                    // current execution file: => get full path
                    arguments.push_back(
                        aula::path::complete(
                            #ifdef _WINDOWS
                                std::move(string::wcstou8(argv[i]))
                            #else
                                argv[i]
                            #endif
                        )
                    );
                    continue;
                }
                arguments.push_back(
                    #ifdef _WINDOWS
                        std::move(string::wcstou8(argv[i]))
                    #else
                        argv[i]
                    #endif
                );
            }
            return std::move(arguments);
        }
    }
}