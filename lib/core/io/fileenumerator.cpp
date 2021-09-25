#include "fileenumerator.h"

#ifdef _WINDOWS
    #include <shlwapi.h>
#else
    #include <dirent.h>
#endif

namespace Aula {
    namespace IO {
        #ifdef _WINDOWS
            /* Windows版FileEnumerator */
            bool FileEnumerator::open(const string &_dir) {
                WIN32_FIND_DATA info;
                
                close();
                dir = Path::appendSlash(_dir);
                if (0 == (handle = (u32)FindFirstFile((Encoding::utf8ToWideString(dir)+L"*.*").c_str(), &info))) {
                    _state = FAILED;
                    _message = "failed to open directory '"+_dir+"'";
                    return false;
                }
                name = Encoding::toUTF8(info.cFileName);
                _state = ACTIVE;
                return true;
            }
            
            void FileEnumerator::close() {
                _state = NONE;
                _message.clear();
                if (handle) {
                    FindClose((HANDLE)handle);
                    handle = 0;
                }
                dir.clear();
                name.clear();
            }
            
            bool FileEnumerator::toNext() {
                WIN32_FIND_DATA info;
                
                if (!handle) return false;
                if (!FindNextFile((HANDLE)handle, &info)) {
                    _state = FINISHED;
                    return false;
                }
                name = Encoding::toUTF8(info.cFileName);
                return true;
            }
        #else
            /* UNIX版FileEnumerator */
            bool FileEnumerator::open(const string &_dir) {
                close();
                dir = Path::appendSlash(_dir);
                if (0 == (handle = (u32)opendir(dir.c_str()))) {
                    _state = FAILED;
                    _message = "failed to open directory '"+_dir+"'";
                    return false;
                }
                struct dirent* dent = readdir((DIR*)handle);
                if (!dent) {
                    _state = FAILED;
                    _message = "failed to read directory '"+_dir+"'";
                    return false;
                }
                name = dent->d_name;
                _state = ACTIVE;
                return true;
            }
            
            void FileEnumerator::close() {
                _state = NONE;
                _message.clear();
                if (handle) {
                    closedir((DIR*)handle);
                    handle = 0;
                }
                dir.clear();
                name.clear();
            }
            
            bool FileEnumerator::toNext() {
                if (!handle) return false;
                
                struct dirent* dent = readdir((DIR*)handle);
                if (!dent) {
                    _state = FINISHED;
                    return false;
                }
                name = dent->d_name;
                return true;
            }
        #endif
    }
}