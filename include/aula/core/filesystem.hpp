#pragma once

#include "path.hpp"
#include <functional>

namespace aula {
    namespace fs {
        /// copy file
        bool copyfile(const std::string &src, const std::string &dest, bool isOverwrite = true);

        /// remove file
        bool rmfile(const std::string &filename);

        /// create directory (recursively)
        bool mkdir(const std::string &dir);

        /// copy directory (recursively)
        bool copydir(const std::string &src, const std::string &dest);

        /// remove directory (recursively)
        bool rmdir(const std::string &dir);

        /// rename (move) file|directory
        bool rename(const std::string &src, const std::string &dest, bool isOverwrite = true);


        /*** ================================================== ***/
        /*** file manager ***/

        typedef std::unique_ptr<FILE, std::function<void(FILE*)>> file_ptr;

        /// open file (supports UTF-8 in Windows)
        // @return unique_ptr<FILE> with custom deleter `fclose`
        inline file_ptr file_open(const std::string &filename, const std::string &mode = "rb") {
            // auto create parent directories if write-mode
            if (mode.find("w") != std::string::npos) mkdir(path::parentdir(filename));
            // force to fopen in binary-mode
            #ifdef _WINDOWS
                return file_ptr(_wfopen(
                    std::move(string::u8towcs(filename)).c_str(),
                    std::move(string::u8towcs(mode.find("b") == std::string::npos ? mode + "b" : mode)).c_str()
                ), fclose);
            #else
                return file_ptr(fopen(
                    filename.c_str(),
                    (mode.find("b") == std::string::npos ? mode + "b" : mode).c_str()
                ), fclose);
            #endif
        }

        /// open pipe (supports UTF-8 in Windows)
        // @return unique_ptr<FILE> with custom deleter `fclose`
        inline file_ptr pipe_open(const std::string &procname, const std::string &mode = "r") {
            #ifdef _WINDOWS
                return file_ptr(_wpopen(std::move(string::u8towcs(procname)).c_str(), std::move(string::u8towcs(mode)).c_str()), _pclose);
            #else
                return file_ptr(popen(procname.c_str(), mode.c_str()), pclose);
            #endif
        }

        /// release file manager explicitly (file or pipe)
        inline void file_close(file_ptr &self) {
            self.reset();
        }

        /// read 1 byte from current pointer
        inline int file_readchar(FILE *self) {
            return fgetc(self);
        }

        /// read 1 line string from current pointer
        std::string file_readline(FILE *self);
    
        /// read specified size of data
        // @return io::binary_ptr|nullptr
        inline io::binary_ptr file_read(FILE *self, size_t size) {
            auto data = io::binary_new(0, size);
            size_t read = fread((void*)io::binary_addr(data.get()), 1, size, self);
            return read > 0 ? std::move(data) : nullptr;
        }

        /// write 1 byte
        inline bool file_writechar(FILE *self, int c) {
            return EOF != fputc(c, self);
        }

        /// write binary data
        // @param size: if -1 is designated => convert to io::binary_size(data)
        // @returns written size
        inline size_t file_write(FILE *self, io::binary_t *data, size_t size = size_t(-1)) {
            return fwrite(io::binary_tostr(data), 1, size == size_t(-1) ? io::binary_size(data) : size, self);
        }
        
        /// seek file pointer
        inline bool file_seek(FILE *self, long offset, io::seekfrom from = io::seekfrom::head) {
            return 0 == fseek(self, offset, from);
        }
        
        /// get current file pointer position
        inline size_t file_pos(FILE *self) {
            return ftell(self);
        }

        /// get file size
        inline size_t file_size(FILE *self) {
            size_t size, cur = file_pos(self); // store current position
            file_seek(self, 0, io::seekfrom::tail);
            size = file_pos(self);
            file_seek(self, cur, io::seekfrom::head); // restore to original position
            return size;
        }
        
        /// flush file stream
        inline bool file_flush(FILE *self) {
            return 0 == fflush(self);
        }

        /*** Utility helper functions ***/
        /// read file content
        // @return io::binary_ptr|nullptr
        inline io::binary_ptr readfile(const std::string &filename) {
            auto fp = file_open(filename, "rb");
            return fp ? file_read(fp.get(), file_size(fp.get())) : nullptr;
        }

        /// write content to file
        inline bool writefile(const std::string &filename, io::binary_t *data) {
            size_t size = io::binary_size(data);
            auto fp = file_open(filename, "wb");
            return fp ? size == file_write(fp.get(), data, size) : false;
        }


        /*** ================================================== ***/
        /*** file enumerator ***/

        /// structure for enumeraing files in directory
        typedef struct {
            unsigned long handler;
            std::string   dir,    // opening directory path
                          current_name, // current file|directory name
                          current_path; // current file|directory path
            bool          current_isfile, current_isdir;
        } dirent_t;

        typedef std::unique_ptr<dirent_t, std::function<void(dirent_t*)>> dirent_ptr;

        /// open directory for enumerating files
        dirent_ptr dir_open(const std::string &dir);

        /// release directory enumerator explicitly
        inline void dir_close(dirent_ptr &self) {
            self.reset();
        }

        /// seek directory to next file / directory
        // @return false if no file / directory any more
        bool dir_next(dirent_t *self);
    }
}