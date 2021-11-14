#include "path.hpp"

#ifdef _WINDOWS
    #include <shlwapi.h>
    #include <sys/stat.h>
#else
    #include <sys/stat.h>
#endif

namespace aula {
    namespace path {
        /// @private search '/' or '\\' from the end, and get the index
        static long __parentsep(const std::string &path, size_t size, long start = -1) {
            long p = (start == -1? size-1: start);
            
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

        /// @private search '.' from the end, and get the index
        static long __firstdot(const std::string &path, size_t size, long start = -1) {
            long p = (start == -1 ? size - 1 : start);
            
            while (p >= 0) {
                // no extension if '/' is found before '.' is found
                if(path[p+1] == '/'
                    #ifdef _WINDOWS
                        || path[p] == '\\'
                    #endif
                ) return -1;
                // it's extension if the pointer isn't ".."
                if (path[p] == '.' && (size_t)p < size - 1 && path[p + 1] != '.') return p;
                --p;
            }
            return -1;
        }

        std::string basename(const std::string &path) {
            size_t size = path.size();
            return size > 0 ? std::move(path.substr(__parentsep(path, size) + 1)) : "";
        }

        std::string stem(const std::string &path) {
            size_t size = path.size();
            if (size == 0) return "";

            long extp = __firstdot(path, size), sep = __parentsep(path, size, extp);
            return std::move(path.substr(sep + 1, extp == -1 ? size_t(-1) : extp - (sep + 1)));
        }

        std::string ext(const std::string &path) {
            size_t size = path.size();
            if (size == 0) return "";

            long extp = __firstdot(path, size);
            return extp > 0 ? std::move(path.substr(extp)) : "";
        }

        std::string parentdir(const std::string &path, bool isFullPathRequired) {
            std::string targetpath = isFullPathRequired ? complete(path) : path;
            size_t size = targetpath.size();
            if (size == 0) return "";

            long p = __parentsep(targetpath, size);
            return p > 0 ? std::move(targetpath.substr(0, p)) : "";
        }

        #ifdef _WINDOWS
            bool isfile(const std::string &path) {
                std::wstring p = std::move(string::u8towcs(path));
                return !PathIsDirectory(p.c_str()) && PathFileExists(p.c_str());
            }
            
            bool isdir(const std::string &path) {
                return FALSE != PathIsDirectory(std::move(string::u8towcs(path)).c_str());
            }
            
            std::string complete(const std::string &path) {
                wchar_t dest[1025];
                if (0 == GetFullPathName(std::move(string::u8towcs(path)).c_str(), 1024, dest, nullptr)) return std::move(path);
                return std::move(string::wcstou8(dest));
            }

            std::unique_ptr<stat_t> stat(const std::string &path) {
                struct _stat s;
                if (_wstat(std::move(string::u8towcs(path)).c_str(), &s) != 0) return nullptr;
                return std::unique_ptr<stat_t>(new stat_t{
                    s.st_dev, s.st_ino, s.st_mode, s.st_nlink,
                    s.st_uid, s.st_gid, s.st_rdev, (unsigned long long)s.st_size,
                    (unsigned long long)s.st_atime, (unsigned long long)s.st_mtime, (unsigned long long)s.st_ctime
                });
            }
        #else
            bool isfile(const std::string &path) {
                struct stat buf;
                return 0 == stat(path.c_str(), &buf) && S_ISREG(buf.st_mode);
            }
            
            bool isdir(const std::string &path) {
                struct stat buf;
                return 0 == stat(path.c_str(), &buf) && S_ISDIR(buf.st_mode);
            }
            
            std::string complete(const std::string &path) {
                char buf[1024 * 4];
                if (nullptr == realpath(path.c_str(), buf)) return path;
                return buf;
            }

            std::unique_ptr<stat_t> stat(const std::string &path) {
                struct stat s;
                if (stat(path.c_str(), &s) != 0) return nullptr;
                return std::unique_ptr<stat_t>(new stat_t{
                    s.st_dev, s.st_ino, s.st_mode, s.st_nlink,
                    s.st_uid, s.st_gid, s.st_rdev, s.st_size,
                    s.st_atim.tv_sec, s.st_mtim.tv_sec, s.st_ctim.tv_sec
                });
            }
        #endif
    }
}