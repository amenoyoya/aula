#include <aula/core/io/filesystem.hpp>

#ifdef _WINDOWS
    #include <shlwapi.h>
#else
    #include <sys/stat.h>
#endif

namespace Aula{
    namespace IO {
        bool copyFile(const std::string &src, const std::string &dest, bool overwrite) {
            if (!overwrite && Path::isFile(dest)) return false;
            
            File in(src, "rb"), out(dest, "wb");
            if (in.getState() == Object::FAILED || out.getState() == Object::FAILED) return false;
            
            auto binary = in.read(in.getSize());
            out.write(*binary, binary->getSize());
            return true;
        }
        
        bool moveFile(const std::string &src, const std::string &dest, bool overwrite) {
            bool isFile = Path::isFile(src), isDir = Path::isDirectory(src);
            
            if (overwrite) {
                if (isFile) {
                    if (Path::isFile(dest) && !removeFile(dest)) return false;
                } else if(isDir) {
                    if (Path::isDirectory(dest) && !removeDirectory(dest)) return false;
                }
            } else {
                if (isFile) {
                    if (Path::isFile(dest)) return false;
                } else if (isDir) {
                    if(Path::isDirectory(dest)) return false;
                }
            }
            #ifdef _WINDOWS
                return FALSE != MoveFile(Encoding::utf8ToWideString(src).c_str(), Encoding::utf8ToWideString(dest).c_str());
            #else
                return 0 == rename(src.c_str(), dest.c_str());
            #endif
        }
        
        
        #ifdef _WINDOWS
            bool createDirectory(const std::string &dir) {
                std::wstring wdir = Encoding::utf8ToWideString(dir);
                wchar_t *p = (wchar_t*)wdir.c_str();
                u32 i = 0;
                
                while (*p != '\0') { // 上位階層のディレクトリから順に作っていく
                    if ((*p == '/' || *p == '\\') && i > 0) {
                        std::wstring name = wdir.substr(0, i);
                        if (!PathIsDirectory(name.c_str())
                            && !CreateDirectory(name.c_str(), nullptr)) return false;
                    }
                    ++p;
                    ++i;
                }
                if (!PathIsDirectory(wdir.c_str())
                    && !CreateDirectory(wdir.c_str(), nullptr)) return false;
                return true;
            }
        #else
            bool createDirectory(const std::string &dir) {
                char *p = (char*)dir.c_str();
                u32 i = 0;
                
                while (*p != '\0') { // 上位階層のディレクトリから順に作っていく
                    if ((*p == '/') && i > 0) {
                        std::string name = dir.substr(0, i);
                        if (!Path::isDirectory(name) && 0 != mkdir(name.c_str(),
                            S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)) return false;
                    }
                    ++p;
                    ++i;
                }
                if (!Path::isDirectory(dir) && 0 != mkdir(dir.c_str(),
                    S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)) return false;
                return true;
            }
        #endif
        
        bool copyDirectory(const std::string &src, const std::string &dest) {
            FileEnumerator f(src);
            std::string dir = Path::appendSlash(dest);
            
            if (f.getState() == Object::FAILED) return false;
            if (!Path::isDirectory(dest) && !createDirectory(dest)) return false;
            do {
                if (f.getName() != "." && f.getName() != "..") {
                    std::string path = f.getPath();
                    
                    if (Path::isDirectory(path)) { // ディレクトリ再帰
                        if(!copyDirectory(path, dir + f.getName())) return false;
                    } else { // ファイルコピー
                        if (!copyFile(path, dir + f.getName())) return false;
                    }
                }
            } while (f.toNext());
            return true;
        }
        
        /// 空ディレクトリ削除
        inline bool rmDir(const std::string &dir) {
            #ifdef _WINDOWS
                return FALSE != RemoveDirectory(Encoding::utf8ToWideString(dir).c_str());
            #else
                return 0 == rmdir(dir.c_str());
            #endif
        }
        
        bool removeDirectory(const std::string &dir) {
            FileEnumerator f(dir);
            
            if (f.getState() == Object::FAILED) return false;
            do {
                if (f.getName() != "." && f.getName() != "..") {
                    std::string path = f.getPath();
                    
                    if (Path::isDirectory(path)) { // ディレクトリは再帰で空にする
                        if (!removeDirectory(path)) return false;
                    } else { // ファイル削除
                        if (!removeFile(path)) return false;
                    }
                }
            } while (f.toNext());
            return rmDir(dir); // 空にしたディレクトリを削除
        }
    }
}