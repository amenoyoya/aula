#include <aula/core/io/fileenumerator.hpp>

#ifdef _WINDOWS
    #include <shlwapi.h>
#else
    #include <dirent.h>
#endif

namespace Aula {
    namespace IO {
        #ifdef _WINDOWS
            /* Windows版FileEnumerator */
            bool FileEnumerator::open(const std::string &_dir) {
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
            bool FileEnumerator::open(const std::string &_dir) {
                close();
                dir = Path::appendSlash(_dir);
                if (0 == (handle = (u32)opendir(dir.c_str()))) {
                    _state = FAILED;
                    _message = "failed to open directory '"+_dir+"'";
                    return false;
                }
                struct dirent* dent = readdir((::DIR*)handle);
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
                    closedir((::DIR*)handle);
                    handle = 0;
                }
                dir.clear();
                name.clear();
            }
            
            bool FileEnumerator::toNext() {
                if (!handle) return false;
                
                struct dirent* dent = readdir((::DIR*)handle);
                if (!dent) {
                    _state = FINISHED;
                    return false;
                }
                name = dent->d_name;
                return true;
            }
        #endif


        /*** ディレクトリ内ファイル列挙 ***/

        /// 基底関数
        static void enumerateFilesBase(std::vector<FileInfo> &dest, const std::string &dir, i32 nest, EnumFileOption opt) {
            if (nest == 0) return;
            
            auto fe = FileEnumerator(dir);
            if (fe.getState() == Object::State::FAILED) return;

            while (fe.toNext()) {
                std::string name = fe.getName();
                if (name == ".." || name == ".") continue;

                FileInfo info;
                info.path = fe.getPath();
                info.isFile = Path::isFile(info.path);
                info.isDirectory = Path::isDirectory(info.path);

                if (info.isFile) {
                    if (opt > 0) dest.push_back(info);
                } else if (info.isDirectory) {
                    if (opt % 2 == 0) dest.push_back(info);
                    enumerateFilesBase(dest, info.path, nest - 1, opt);
                }
            }
        }

        std::vector<FileInfo> enumerateFiles(const std::string &dir, i32 nest, EnumFileOption opt) {
            std::vector<FileInfo> files;

            enumerateFilesBase(files, dir, nest, opt);
            return std::move(files);
        }
    }
}