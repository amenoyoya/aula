#include <aula/core/path/base.hpp>

#ifdef _WINDOWS
    #include <shlwapi.h>
#else
    #include <sys/stat.h>
#endif

namespace Aula {
    namespace Path {
        /// '/'か'\\'まで後方から検索
        static i32 getParentSep(const std::string &path, u32 size, i32 start = -1) {
            i32 p = (start == -1? size-1: start);
            
            while (path[p] != '/'
                #ifdef _WINDOWS
                    && path[p] != '\\'
                #endif
                )
            {
                if (p == 0) return -1;
                --p;
            }
            return p;
        }
        
        /// '.'まで後方から検索
        static i32 getFirstDot(const std::string &path, u32 size, i32 start = -1) {
            i32 p = (start == -1? size-1: start);
            
            while (p >= 0) {
                // '.'が見つかる前に'/'が見つかった場合は拡張子なし
                if(path[p+1] == '/'
                    #ifdef _WINDOWS
                        || path[p] == '\\'
                    #endif
                ) return -1;
                // '.'の直後が'.'でなければ拡張子
                if (path[p] == '.' && (u32)p < size-1 && path[p+1] != '.') return p;
                --p;
            }
            return -1;
        }
        
        std::string getBaseName(const std::string &path) {
            u32 size = path.size();
            return size > 0? std::move(path.substr(getParentSep(path, size)+1)): "";
        }
        
        std::string getBaseStem(const std::string &path) {
            u32 size = path.size();
            if (size > 0) {
                i32 extp = getFirstDot(path, size),
                    sep = getParentSep(path, size, extp);
                return std::move(path.substr(sep+1, extp == -1? u32(-1): extp-(sep+1)));
            }
            return "";
        }
        
        std::string getExtension(const std::string &path) {
            u32 size = path.size();
            
            if (size > 0) {
                i32 extp = getFirstDot(path, size);
                if (extp > 0) return std::move(path.substr(extp));
                return "";
            }
            return "";
        }
        
        std::string getParentDirectory(const std::string &path, bool real) {
            if (real) {
                std::string realpath = complete(path);
                u32 size = realpath.size();
                if (size > 0) {
                    i32 p = getParentSep(realpath, size);
                    return p > 0? realpath.substr(0, p): "";
                }
                return "";
            } else {
                u32 size = path.size();
                if(size > 0){
                    i32 p = getParentSep(path, size);
                    return p > 0? std::move(path.substr(0, p)): "";
                }
                return "";
            }
        }
        
        std::string convert(const std::string &path) {
            std::string dest;
            char *p = (char*)path.c_str();
            bool sep = true;
            
            while (*p != 0) {
                if (sep && *p == '.') {
                    if (*(p+1) == '/'
                        #ifdef _WINDOWS
                            || *(p+1) == '\\'
                        #endif
                    ) {
                        p += 2;
                        continue;
                    } else if (*(p+1) == '.' && (*(p+2) == '/'
                        #ifdef _WINDOWS
                            || *(p+2) == '\\'
                        #endif
                    )) {
                        char c = (dest.empty()? 0: *(dest.end()-1));
                        p += 3;
                        if (!dest.empty()) dest.erase(dest.end()-1);
                        dest = getParentDirectory(dest, false);
                        if (c) dest.push_back(c);
                        continue;
                    }
                }
                
                if (*p == '/' || *p == '\\') sep = true;
                else sep = false;
                
                dest.push_back(*p);
                ++p;
            }
            return std::move(dest);
        }
        
        bool isSame(const std::string &path1, const std::string &path2, u32 len) {
            unsigned char *p1 = (unsigned char*)path1.c_str(), *p2 = (unsigned char*)path2.c_str();
            u32 i = 0;
            
            while (*p1 || *p2) {
                if (len != (u32)-1 && len == i) return true;
                #if defined(_WINDOWS)
                    if (toupper(*p1) != toupper(*p2) && !((*p1 == '/' && *p2 == '\\') || (*p1 == '\\' && *p2 == '/'))) return false;
                #elif defined(_APPLE)
                    if (toupper(*p1) != toupper(*p2)) return false;
                #else
                    if (*p1 != *p2) return false;
                #endif
                ++p1;
                ++p2;
                ++i;
            }
            return true;
        }
        
        #ifdef _WINDOWS
            /* Windows版ファイル判定,フルパス取得など */
            bool isFile(const std::string &path) {
                std::wstring p = Encoding::utf8ToWideString(path);
                return !PathIsDirectory(p.c_str()) && PathFileExists(p.c_str());
            }
            
            bool isDirectory(const std::string &path) {
                return FALSE != PathIsDirectory(Encoding::utf8ToWideString(path).c_str());
            }
            
            std::string complete(const std::string &path) {
                wchar_t dest[1024];
                if (0 == GetFullPathName(Encoding::utf8ToWideString(path).c_str(), 1024, dest, nullptr)) return path;
                return std::move(Encoding::toUTF8(dest));
            }
            
            std::string appendSlash(const std::string &path) {
                auto it = path.end() - 1;
                if (*it != '/' && *it != '\\') return path + "\\";
                return std::move(path);
            }
            
            std::string removeSlash(std::string path) {
                auto it = path.end() - 1;
                if (*it == '/' || *it == '\\') path.erase(it);
                return std::move(path);
            }
        #else
            /* UNIX版ファイル判定,フルパス取得など */
            bool isFile(const std::string &path) {
                struct stat buf;
                return 0 == stat(path.c_str(), &buf) && S_ISREG(buf.st_mode);
            }
            
            bool isDirectory(const std::string &path) {
                struct stat buf;
                return 0 == stat(path.c_str(), &buf) && S_ISDIR(buf.st_mode);
            }
            
            std::string complete(const std::string &path) {
                char buf[1024 * 4];
                if (nullptr == realpath(path.c_str(), buf)) return path;
                return buf;
            }
            
            std::string appendSlash(const std::string &path){
                auto it = path.end() - 1;
                if (*it != '/') return path + "/";
                return std::move(path);
            }
            
            std::string removeSlash(std::string path){
                auto it = path.end() - 1;
                if (*it == '/') path.erase(it);
                return std::move(path);
            }
        #endif
    }
}