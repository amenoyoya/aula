#include "filesystem.hpp"

#ifdef _WINDOWS
    #include <shlwapi.h>
#else
    #include <sys/stat.h>
    #include <dirent.h>
#endif

namespace aula {
    namespace fs {
        bool copyfile(const std::string &src, const std::string &dest, bool isOverwrite) {
            if (!isOverwrite && path::isfile(dest)) return false;
            
            auto content = readfile(src);
            return content ? writefile(dest, content.get()) : false;
        }

        bool rmfile(const std::string &filename) {
            #ifdef _WINDOWS
                return FALSE != DeleteFileW(std::move(string::u8towcs(filename)).c_str());
            #else
                return 0 == unlink(filename.c_str());
            #endif
        }

        #ifdef _WINDOWS
            bool mkdir(const std::string &dir) {
                std::wstring wdir = std::move(string::u8towcs(dir));
                wchar_t *p = (wchar_t*)wdir.c_str();
                unsigned long i = 0;
                // create directories in order from the upper level directory
                while (*p != '\0') {
                    if ((*p == '/' || *p == '\\') && i > 0) {
                        std::wstring name = wdir.substr(0, i);
                        if (!PathIsDirectory(name.c_str()) && !CreateDirectory(name.c_str(), nullptr)) return false;
                    }
                    ++p;
                    ++i;
                }
                if (!PathIsDirectory(wdir.c_str()) && !CreateDirectory(wdir.c_str(), nullptr)) return false;
                return true;
            }
        #else
            bool mkdir(const std::string &dir) {
                char *p = (char*)dir.c_str();
                unsigned long i = 0;
                // create directories in order from the upper level directory
                while (*p != '\0') {
                    if ((*p == '/') && i > 0) {
                        std::string name = dir.substr(0, i);
                        if (!path::isdir(name) && 0 != ::mkdir(name.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)) return false;
                    }
                    ++p;
                    ++i;
                }
                if (!path::isdir(dir) && 0 != ::mkdir(dir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)) return false;
                return true;
            }
        #endif
        
        bool copydir(const std::string &src, const std::string &dest) {
            auto dirent = dir_open(src);
            if (!dirent) return false;
            if (!path::isdir(dest) && !mkdir(dest)) return false;

            std::string dir = std::move(path::append_slash(dest));
            do {
                if (dirent->current_name == "." || dirent->current_name == "..") continue;

                if (dirent->current_isdir) {
                    // copy directory recursively
                    if (!copydir(dirent->current_path, dir + dirent->current_name)) return false;
                } else if (dirent->current_isfile) {
                    // copy file
                    if (!copyfile(dirent->current_path, dir + dirent->current_name)) return false;
                }
            } while (dir_next(dirent.get()));
            return true;
        }
        
        /// @private remove empty directory
        inline bool rmdir_empty(const std::string &dir) {
            #ifdef _WINDOWS
                return FALSE != RemoveDirectory(std::move(string::u8towcs(dir)).c_str());
            #else
                return 0 == ::rmdir(dir.c_str());
            #endif
        }
        
        bool rmdir(const std::string &dir) {
            auto dirent = dir_open(dir);
            if (!dirent) return false;

            do {
                if (dirent->current_name == "." || dirent->current_name == "..") continue;
                
                if (dirent->current_isdir) {
                    // remove directory recursively
                    if (!rmdir(dirent->current_path)) return false;
                } else if (dirent->current_isfile) {
                    // remove file
                    if (!rmfile(dirent->current_path)) return false;
                }
            } while (dir_next(dirent.get()));
            return rmdir_empty(dir); // remove empty directory
        }

        /// @private rename file|directory
        inline bool rename_base(const std::string &src, const std::string &dest) {
            return 0 ==
                #ifdef _WINDOWS
                    _wrename(std::move(string::u8towcs(src)).c_str(), std::move(string::u8towcs(dest)).c_str());
                #else
                    rename(src.c_str(), dest.c_str());
                #endif
        }

        bool rename(const std::string &src, const std::string &dest, bool isOverwrite) {
            bool isdir = path::isdir(dest), isfile = path::isfile(dest);
            if (!isdir && !isfile) return rename_base(src, dest);
            if (isOverwrite) {
                if (isdir) return rmdir(dest) && rename_base(src, dest);
                if (isfile) return rmfile(dest) && rename_base(src, dest);
            }
            return false;
        }

        /*** ================================================== ***/
        /*** file manager ***/

        /// @private custom file deleter
        inline void file_deleter(file_t *self) {
            if (!self) return;
            if (self->handler) fclose((FILE*)self->handler);
            delete self;
            self = nullptr;
        }

        /// @private custom pipe deleter
        inline void pipe_deleter(file_t *self) {
            if (!self) return;
            if (self->handler) {
                #ifdef _WINDOWS
                    _pclose((FILE*)self->handler);
                #else
                    pclose((FILE*)self->handler);
                #endif
            }
            delete self;
            self = nullptr;
        }

        /// @private get file size
        inline size_t file_size(FILE *self) {
            size_t size, cur = ftell(self); // store current position
            fseek(self, 0, io::seekfrom::tail);
            size = ftell(self);
            fseek(self, cur, io::seekfrom::head); // restore to original position
            return size;
        }

        file_ptr file_open(const std::string &filename, const std::string &mode) {
            // auto create parent directories if write-mode
            if (mode.find("w") != std::string::npos) mkdir(path::parentdir(filename));
            // force to fopen in binary-mode
            FILE *fp =
            #ifdef _WINDOWS
                _wfopen(
                    std::move(string::u8towcs(filename)).c_str(),
                    std::move(string::u8towcs(mode.find("b") == std::string::npos ? mode + "b" : mode)).c_str()
                );
            #else
                fopen(
                    filename.c_str(),
                    (mode.find("b") == std::string::npos ? mode + "b" : mode).c_str()
                );
            #endif
            if (!fp) return nullptr;
            // get file size
            size_t size = file_size(fp);
            return file_ptr(new file_t { (unsigned long)fp, size }, file_deleter);
        }

        file_ptr pipe_open(const std::string &procname, const std::string &mode) {
            unsigned long handler =
            #ifdef _WINDOWS
                (unsigned long)_wpopen(std::move(string::u8towcs(procname)).c_str(), std::move(string::u8towcs(mode)).c_str());
            #else
                (unsigned long)popen(procname.c_str(), mode.c_str());
            #endif
            if (handler == 0) return nullptr;
            return file_ptr(new file_t { handler, 0 }, pipe_deleter);
        }

        std::string file_readline(file_t *self) {
            if (!self || !self->handler) return "";
            
            std::string line;
            line.reserve(512);
            for (int c = file_readchar(self); c != EOF; c = file_readchar(self)) {
                // break loop if crlf found
                if (c == '\r') {
                    file_seek(self, 1, io::seekfrom::cur); // skip next \n
                    break;
                } else if (c == '\n') {
                    break;
                }
                line.push_back((char)c);
            }
            return std::move(line);
        }

        /*** ================================================== ***/
        /*** file enumerator ***/
        #ifdef _WINDOWS
            /// @private custom deleter for dirent_ptr
            static void dir_deleter(dirent_t *self) {
                if (self == nullptr) return;
                if (self->handler) {
                    FindClose((HANDLE)self->handler);
                    self->handler = 0;
                }
                delete self;
                self = nullptr;
            }

            dirent_ptr dir_open(const std::string &_dir) {
                if (!path::isdir(_dir)) return nullptr; // not directory

                WIN32_FIND_DATA info;
                std::string dir = std::move(path::append_slash(_dir));
                unsigned long handler = (unsigned long)FindFirstFile((std::move(string::u8towcs(dir)) + L"*.*").c_str(), &info);

                if (handler == 0) return nullptr;
                std::string name = std::move(string::wcstou8(info.cFileName));
                std::string path = std::move(dir + name);
                bool isfile = path::isfile(path), isdir = path::isdir(path);
                return dirent_ptr(new dirent_t {
                    handler, std::move(dir), std::move(name), std::move(path), isfile, isdir
                }, dir_deleter);
            }
            
            bool dir_next(dirent_t *self) {
                WIN32_FIND_DATA info;
                if (!FindNextFile((HANDLE)self->handler, &info)) return false;
                self->current_name = std::move(string::wcstou8(info.cFileName));
                self->current_path = self->dir + self->current_name;
                self->current_isfile = path::isfile(self->current_path);
                self->current_isdir = path::isdir(self->current_path);
                return true;
            }
        #else
            /// @private custom deleter for dirent_ptr
            static void dir_deleter(dirent_t *self) {
                if (self == nullptr) return;
                if (self->handler) {
                    closedir((DIR*)self->handler);
                    self->handler = 0;
                }
                delete self;
                self = nullptr;
            }

            dirent_ptr dir_open(const std::string &_dir) {
                if (!path::isdir(_dir)) return nullptr; // not directory

                std::string dir = std::move(path::append_slash(_dir));
                unsigned long handler = (unsigned long)opendir(dir.c_str());

                if (0 == handler) return nullptr;

                struct dirent* dent = readdir((DIR*)handler);
                if (!dent) {
                    closedir((DIR*)handler);
                    return nullptr;
                }
                std::string name = dent->d_name, path = std::move(dir + name);
                bool isfile = path::isfile(path), isdir = path::isdir(path);
                return dirent_ptr(new dirent_t {
                    handler, std::move(dir), std::move(name), std::move(path), isfile, isdir
                }, dir_deleter);
            }

            bool dir_next(dirent_t *self) {
                struct dirent* dent = readdir((DIR*)self->handler);
                if (!dent) return false;
                self->current_name = dent->d_name;
                self->current_path = self->dir + self->current_name;
                self->current_isfile = path::isfile(self->current_path);
                self->current_isdir = path::isdir(self->current_path);
                return true;
            }
        #endif
    }
}