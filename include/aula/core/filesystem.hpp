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

        struct file_t {
            unsigned long handler; // FILE*
            size_t size; // file size
        };
        typedef std::unique_ptr<file_t, std::function<void(file_t*)>> file_ptr;

        /// open file (supports UTF-8 in Windows)
        // @return unique_ptr<FILE> with custom deleter `fclose`
        file_ptr file_open(const std::string &filename, const std::string &mode = "rb");

        /// open pipe (supports UTF-8 in Windows)
        // @return unique_ptr<FILE> with custom deleter `pclose`
        file_ptr pipe_open(const std::string &procname, const std::string &mode = "r");

        /// release file manager explicitly (file or pipe)
        inline void file_close(file_ptr &self) {
            self.reset();
        }

        /// read 1 byte from current pointer
        inline int file_readchar(file_t *self) {
            return self && self->handler ? fgetc((FILE*)self->handler) : EOF;
        }

        /// read 1 line string from current pointer
        std::string file_readline(file_t *self);
    
        /// read specified size of data
        // @return io::binary_ptr|nullptr
        inline io::binary_ptr file_read(file_t *self, size_t size) {
            if (!self || !self->handler) return nullptr;
            auto data = io::binary_new(0, size);
            size_t read = fread((void*)io::binary_addr(data.get()), 1, size, (FILE*)self->handler);
            return read > 0 ? std::move(data) : nullptr;
        }

        /// write 1 byte
        inline bool file_writechar(file_t *self, int c) {
            return self && self->handler ? EOF != fputc(c, (FILE*)self->handler) : false;
        }

        /// write binary data
        // @returns written size
        inline size_t file_write(file_t *self, io::binary_t *data) {
            return self && self->handler ? fwrite(io::binary_tostr(data), 1, data->size, (FILE*)self->handler) : 0;
        }
        
        /// seek file pointer
        inline bool file_seek(file_t *self, long offset, io::seekfrom from = io::seekfrom::head) {
            return self && self->handler ? 0 == fseek((FILE*)self->handler, offset, from) : false;
        }
        
        /// get current file pointer position
        inline size_t file_pos(file_t *self) {
            return self && self->handler ? ftell((FILE*)self->handler) : EOF;
        }
        
        /// flush file stream
        inline bool file_flush(file_t *self) {
            return self && self->handler ? 0 == fflush((FILE*)self->handler) : false;
        }

        /*** Utility helper functions ***/
        /// read file content
        // @return io::binary_ptr|nullptr
        inline io::binary_ptr readfile(const std::string &filename) {
            auto fp = file_open(filename, "rb");
            return fp ? file_read(fp.get(), fp->size) : nullptr;
        }

        /// write content to file
        inline bool writefile(const std::string &filename, io::binary_t *data) {
            auto fp = file_open(filename, "wb");
            return fp ? data->size == file_write(fp.get(), data) : false;
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