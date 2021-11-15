#pragma once

#include "string.hpp"
#include <memory>
#include <clocale>

#ifdef _WINDOWS
    #include <io.h> // _setmode
    #include <fcntl.h> // _O_U16TEXT
#endif

namespace aula {
    namespace io {
        #ifdef _WINDOWS
            /// set wide string mode to stdio (windows only)
            inline void setu16mode(FILE *fp) {
                _setmode(_fileno(fp), _O_U16TEXT);
            }
        #endif

        /// initialize locale
        // on windows: set wide string mode to stdio file pointer (measures against garbled characters in multibyte languages)
        inline void initlocale() {
            setlocale(LC_ALL, "");
            #ifdef _WINDOWS
                setu16mode(stdout);
                setu16mode(stderr);
                setu16mode(stdin);
            #endif
        }

        /// UTF-8 supported stdout
        inline int putstr(FILE *fp, const std::string &str) {
            return fputws(std::move(string::u8towcs(str)).c_str(), fp);
        }

        /// UTF-8 supported stdin
        inline std::string getstr(FILE *fp, size_t size = 512) {
            wchar_t *buffer = new wchar_t[size + 1];
            std::string result = std::move(string::wcstou8(fgetws(buffer, size, fp)));
            delete[] buffer;
            result.erase(result.end() - 1); // remove \n
            return std::move(result);
        }

        /*** ================================================== ***/
        /*** binary manager ***/

        /// io seek_from enum
        enum seekfrom {
            head, cur, tail
        };

        /// binary management structure
        struct binary_t {
            std::string data;
            unsigned long head, iter, size;
        };
        typedef std::unique_ptr<binary_t> binary_ptr;

        /// create new binary from pointer address (copy)
        // @param pointer: if 0 is designated => empty binary data will be created, else => create copied data from pointer
        binary_ptr binary_new(unsigned long pointer, size_t size);

        /// create new binary from string (copy)
        // @param data: if null is designated => empty binary data will be created, else => create copied data from string
        // @param size: if -1 is designated => convert to strlen(data)
        inline binary_ptr binary_newstr(const char *data, size_t size = size_t(-1)) {
            return std::move(binary_new((unsigned long)data, size == size_t(-1) ? strlen(data) : size));
        }

        /// open binary as management target from pointer address
        // @param pointer: memory address of the target data (just copy pointer, ownership will not be moved)
        inline binary_ptr binary_open(unsigned long pointer, size_t size) {
            auto self = binary_ptr(new binary_t {"", pointer, 0, size});
            return std::move(self);
        }

        /// open binary as management target from string
        // @param size: if -1 is designated => convert to strlen(data)
        inline binary_ptr binary_openstr(const char *data, size_t size = size_t(-1)) {
            return std::move(binary_open((unsigned long)data, size == size_t(-1) ? strlen(data) : size));
        }

        /// release binary manager explicitly
        inline void binary_close(binary_ptr &self) {
            return self.reset();
        }

        /// resize allocated memory size (only new binary)
        // iterator position will be set to head
        void binary_resize(binary_t *self, size_t size);

        /// reserve memory allocation (only new binary)
        inline void binary_reserve(binary_t *self, size_t size) {
            if (!self->data.empty()) self->data.reserve(size);
        }

        /// get raw pointer address
        inline unsigned long binary_addr(binary_t *self, unsigned long from = 0) {
            return self->head + from;
        }

        /// get raw pointer as string
        inline const char *binary_tostr(binary_t *self, unsigned long from = 0) {
            return (const char*)(self->head + from);
        }

        /// append data (only new binary)
        inline void binary_push(binary_t *self, const void *data, size_t size) {
            if (!self->data.empty()) {
                size_t oldsize = self->size;
                binary_resize(self, oldsize + size);
                memcpy((void*)(self->head + oldsize), data, size);
            }
        }
        
        /// append integer as binary (only new binary)
        inline void binary_pushint(binary_t *self, int data, size_t size = 4) {
            binary_push(self, &data, size);
        }

        /// append string as binary (only new binary)
        // @param size: if size_t(-1) is designated => convert to data.size()
        inline void binary_pushstr(binary_t *self, const std::string &data, size_t size = size_t(-1)) {
            binary_push(self, data.c_str(), size == size_t(-1) ? data.size() : size);
        }

        /// append string with its size as binary (only new binary)
        inline void binary_pushrune(binary_t *self, const std::string &data) {
            binary_pushint(self, data.size());
            binary_pushstr(self, data, data.size());
        }

        /// append double precision number as binary (only new_inary)
        inline void binary_pushnum(binary_t *self, double data, unsigned short precision = 6) {
            binary_pushstr(self, string::tostr(data, precision));
        }

        /// seek binary pointer iterator
        void binary_seek(binary_t *self, long pos, seekfrom from = seekfrom::head);

        /// get integer from current binary iterator
        template<typename T>
        T binary_get(binary_t *self) {
            T buf = 0;
            memcpy(&buf, (const char*)(self->head + self->iter), sizeof(T));
            binary_seek(self, sizeof(T), seekfrom::cur);
            return buf;
        }
        inline long binary_geti32(binary_t *self) {
            return binary_get<long>(self);
        }
        inline unsigned long binary_getu32(binary_t *self) {
            return binary_get<unsigned long>(self);
        }
        inline short binary_geti16(binary_t *self) {
            return binary_get<short>(self);
        }
        inline unsigned short binary_getu16(binary_t *self) {
            return binary_get<unsigned short>(self);
        }
        inline char binary_geti8(binary_t *self) {
            return binary_get<char>(self);
        }
        inline unsigned char binary_getu8(binary_t *self) {
            return binary_get<unsigned char>(self);
        }

        /// get specified size of string from current binary iterator
        inline std::string binary_getstr(binary_t *self, size_t size) {
            std::string dest;
            if (size == 0) return "";
            if (self->iter + size >= self->size) return (const char*)(self->head + self->iter);
            dest.resize(size + 1);
            memcpy((void*)dest.c_str(), (const void*)(self->head + self->iter), size);
            binary_seek(self, size, seekfrom::cur);
            return dest.c_str();
        }
        
        /// get string which is embedded by binary_pushrune() from current binary iterator
        inline std::string binary_getrune(binary_t *self) {
            size_t size = binary_getu32(self);
            return std::move(binary_getstr(self, size));
        }

        /// get double precision number from current binary iterator
        inline double binary_getnum(binary_t *self) {
            return strtod(binary_getrune(self).c_str(), nullptr);
        }

        /// get crc32 of the binary
        unsigned long binary_crc32(binary_t *self, unsigned long start = 0xffffffff);

        /// easy encryption of the binary by specified key (only new binary)
        // @return false if the binary is not new binary
        bool binary_encrypt(binary_t *self, const std::string &key, size_t keysize = 16);

        /// easy decryption of the binary by specified key (only new binary)
        // @return false if the binary is not new binary or the key is different from encrypt key
        bool binary_decrypt(binary_t *self, const std::string &key, size_t keysize = 16);
    }
}