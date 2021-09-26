#include "libraryloader.hpp"

#ifndef _WINDOWS
    #include <unistd.h>
#endif

namespace Aula {
    namespace System {
        bool LibraryLoader::open(const std::string &path) {
            close();
            #ifdef _WINDOWS
                if (0 == (handle = (u32)LoadLibrary(Encoding::utf8ToWideString(path).c_str()))) {
                    _state = FAILED;
                    _message = "failed to open library '"+path+"'";
                    return false;
                }
            #else
                if (0 == (handle = (u32)dlopen(path.c_str(), RTLD_LAZY))) {
                    _state = FAILED;
                    _message = "failed to open library '"+path+"'";
                    return false;
                }
            #endif
            _state = ACTIVE;
            return true;
        }
        
        void LibraryLoader::close() {
            _state = NONE;
            _message.clear();
            if (handle) {
                #ifdef _WINDOWS
                    FreeLibrary((HMODULE)handle); handle = 0;
                #else
                    dlclose((void*)handle); handle = 0;
                #endif
            }
        }
    }
}