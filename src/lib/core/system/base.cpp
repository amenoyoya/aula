#include <aula/core/system/base.hpp>

#ifdef _WINDOWS
    #include <mmsystem.h>
#else
    #include <sys/time.h>
#endif

namespace Aula {
    namespace System {
        u32 getTime() {
            #ifdef _WINDOWS
                return timeGetTime();
            #else
                struct timeval tv;
                gettimeofday(&tv, nullptr);
                return tv.tv_sec * 1000 + tv.tv_usec / 1000;
            #endif
        }
        
        std::string getEnvironmentVariable(const std::string &env) {
            #ifdef _WINDOWS
                std::wstring name = Encoding::utf8ToWideString(env), buf;
                u32 size = GetEnvironmentVariable(name.c_str(), nullptr, 0);
                
                if(size == 0) return "";
                buf.resize(size);
                GetEnvironmentVariable(name.c_str(), (wchar_t*)buf.c_str(), size);
                return std::move(Encoding::toUTF8(buf));
            #else
                char *ret = getenv(env.c_str());
                return nullptr == ret? "": ret;
            #endif
        }
        
        #ifdef _WINDOWS
            std::string getCurrentDirectory() {
                wchar_t dest[512];
                GetCurrentDirectory(512, dest);
                return std::move(Encoding::toUTF8(dest));
            }
        #else
            std::string getCurrentDirectory() {
                char dest[512];
                return getcwd(dest, 512);
            }
        #endif
    }
}