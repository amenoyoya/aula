#include "archiver.hpp"
#include <zlib.h>
#include <zip.h>
#include <unzip.h>
#include <time.h>

namespace aula {
    namespace zip {
        /// @private get file size
        inline size_t __get_filesize(const char *filename) {
            auto fp = fs::file_open(filename, "rb");
            return fp ? fs::file_size(fp.get()) : 0;
        }

        /// @private get current date time
        static bool __get_datetime(tm_zip *dest) {
            struct tm *t;
            time_t timer = (time_t)time(nullptr);
            
            if(nullptr == (t = localtime(&timer))) return false;
            dest->tm_year = t->tm_year + 1900;
            dest->tm_mon = t->tm_mon + 1;
            dest->tm_mday = t->tm_mday;
            dest->tm_hour = t->tm_hour;
            dest->tm_min = t->tm_min;
            dest->tm_sec = t->tm_sec;
            return true;
        }

        /// @private get DOS date
        inline unsigned short __get_dosdate(unsigned long year, unsigned long month, unsigned long day) {
            return (unsigned short)(((unsigned)(year - 1980) << 9) | ((unsigned)month << 5) | (unsigned)day);
        }

        /// @private get DOS time
        inline unsigned short __get_dostime(unsigned long hour, unsigned long minute, unsigned long second) {
            return (unsigned short)(((unsigned)hour << 11) | ((unsigned)minute << 5) | ((unsigned)second >> 1));
        }

        /// @private replace "\" to "/"
        inline std::string &__exchange_path(std::string &dest) {
            for (char *p = (char*)dest.c_str(); *p; ++p) if(*p == '\\') *p = '/';
            return dest;
        }

        /*** @private zlib helper functions ***/
        #ifdef _WINDOWS
            #define ENCODE(str) std::move(aula::string::u8towcs(str)).c_str()
            #define _FOPEN(open) _w##open
            #define _STRING(str) L##str
        #else
            #define ENCODE(str) str
            #define _FOPEN(open) open
            #define _STRING(str) str
        #endif
        #define FOPEN(open, path, mode) _FOPEN(open)(ENCODE(path), mode)

        static voidpf ZCALLBACK __open_file_func(voidpf opaque, const char* filename, int mode) {
            FILE *file = nullptr;
            #ifdef _WINDOWS
                const wchar_t* mode_fopen = nullptr;
            #else
                const char* mode_fopen = nullptr;
            #endif
            
            if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER) == ZLIB_FILEFUNC_MODE_READ) mode_fopen = _STRING("rb");
            else if (mode & ZLIB_FILEFUNC_MODE_EXISTING) mode_fopen = _STRING("r+b");
            else if (mode & ZLIB_FILEFUNC_MODE_CREATE) mode_fopen = _STRING("wb");
            
            if (mode_fopen) {
                if (mode_fopen[0] == 'w') fs::mkdir(path::parentdir(filename).c_str()); // create parent directories recursively
                file = FOPEN(fopen, filename, mode_fopen);
            }
            return file;
        }

        #undef ENCODE
        #undef _FOPEN
        #undef _STRING
        #undef FOPEN

        inline uLong ZCALLBACK __read_file_func(voidpf opaque, voidpf stream, void* buf, uLong size) {
            return (uLong)fread(buf, 1, (size_t)size, (FILE *)stream);
        }

        inline uLong ZCALLBACK __write_file_func(voidpf opaque, voidpf stream, const void* buf, uLong size) {
            return (uLong)fwrite(buf, 1, (size_t)size, (FILE *)stream);
        }

        inline long ZCALLBACK __tell_file_func(voidpf opaque, voidpf stream) {
            return ftell((FILE *)stream);
        }

        static long ZCALLBACK __seek_file_func(voidpf opaque, voidpf stream, uLong offset, int origin) {
            int fseek_origin = 0;
            long ret = 0;

            switch (origin) {
            case ZLIB_FILEFUNC_SEEK_CUR:
                fseek_origin = SEEK_CUR;
                break;
            case ZLIB_FILEFUNC_SEEK_END:
                fseek_origin = SEEK_END;
                break;
            case ZLIB_FILEFUNC_SEEK_SET:
                fseek_origin = SEEK_SET;
                break;
            default:
                return -1;
            }
            
            if (fseek((FILE *)stream, offset, fseek_origin) != 0) ret = -1;
            return ret;
        }

        inline int ZCALLBACK __close_file_func(voidpf opaque, voidpf stream) {
            return fclose((FILE *)stream);
        }

        inline int ZCALLBACK __error_file_func(voidpf opaque, voidpf stream) {
            return ferror((FILE *)stream);
        }

        /// @private file controll functions map
        static zlib_filefunc_def __file_func_map = {
            __open_file_func, __read_file_func, __write_file_func, __tell_file_func,
            __seek_file_func, __close_file_func, __error_file_func, nullptr
        };

        /// @private custom deleter for zip archiver
        inline void zip_deleter(archiver_t *self) {
            if (!self) return;
            if (self->handler) zipClose((zipFile)self->handler, self->comment.empty() ? nullptr : self->comment.c_str());
            delete self;
            self = nullptr;
        }

        archiver_ptr zip_open(const std::string &filename, const std::string &mode) {
            unsigned short type;
            if (mode == "w") type = 0;
            else if (mode == "w+") type = 1;
            else if (mode == "a") type = 2;
            else return nullptr;

            unsigned long handler = (unsigned long)zipOpen2(filename.c_str(), type, nullptr, &__file_func_map);
            return handler ? archiver_ptr(new archiver_t { handler, 0 }, zip_deleter) : nullptr; 
        }

        bool zip_append(archiver_t *self, io::binary_t *data, const std::string &dest_filename, const std::string &comment) {
            if (!self || !self->handler) return false;

            zip_fileinfo info;
            std::string name = dest_filename;
            __get_datetime(&info.tmz_date);
            info.dosDate = __get_dosdate(info.tmz_date.tm_year, info.tmz_date.tm_mon, info.tmz_date.tm_mday);
            info.internal_fa = 0;
            info.external_fa = 0;
            // supports UTF-8: flagBase = 1<<11
            if (ZIP_OK != zipOpenNewFileInZip4((zipFile)self->handler,
                __exchange_path(name).c_str(), &info, nullptr, 0,
                nullptr, 0, comment.empty() ? nullptr : comment.c_str(), Z_DEFLATED, self->compresslevel,
                0, 15, 8, Z_DEFAULT_STRATEGY, self->password.empty() ? nullptr : self->password.c_str(),
                io::binary_crc32(data, 0xffffffff), 36, 1 << 11))
            {
                return false;
            }
            bool result = ZIP_OK == zipWriteInFileInZip((zipFile)self->handler, io::binary_tostr(data), io::binary_size(data));
            zipCloseFileInZip((zipFile)self->handler);
            return result;
        }


        /// @private get zip data size (supports embedded zip data)
        static size_t get_zipsize(extractor_t *self, const char *filename) {
            if (!self || !self->handler) return 0;

            size_t offset = unz_offset(self); // get zip data offset
            size_t filesize = 0; // total size of files in the zip data
            for (bool flag = unz_locate_first(self); flag; flag = unz_locate_next(self)) {
                // get the local file header size + compressed size
                auto info = unz_info(self);
                if (!info) return 0;
                filesize += info->compressed_size + info->filename_size + info->extra_size + 30;
            }
            unz_locate_first(self); // restore local file position to the first
            return __get_filesize(filename) - (offset - filesize);
        }

        /// @private get zip global information
        static bool get_zipinfo(extractor_t *self) {
            if (!self || !self->handler) return false;

            unz_global_info info;
            if (UNZ_OK != unzGetGlobalInfo((unzFile)self->handler, &info)) return false;

            self->entries = info.number_entry;
            self->comment.clear();
            self->comment.resize(info.size_comment);
            return info.size_comment == unzGetGlobalComment((unzFile)self->handler, (char*)self->comment.c_str(), info.size_comment);
        }

        /// @private custom deleter for zip extractor
        inline void unz_deleter(extractor_t *self) {
            if (!self) return;
            if (self->handler) unzClose((unzFile)self->handler);
            delete self;
            self = nullptr;
        }

        extractor_ptr unz_open(const std::string &filename) {
            unsigned long handler = (unsigned long)unzOpen2(filename.c_str(), &__file_func_map);
            if (!handler) return nullptr;

            auto self = extractor_ptr(new extractor_t{ handler, 0, 0, 0 }, unz_deleter);
            // get zip global info
            if (!get_zipinfo(self.get())) return nullptr;
            // calculate zip data size
            self->size = get_zipsize(self.get(), filename.c_str());
            return std::move(self);
        }

        bool unz_locate_first(extractor_t *self) {
            return self && self->handler ? UNZ_OK == unzGoToFirstFile((unzFile)self->handler) : false;
        }

        bool unz_locate_next(extractor_t *self) {
            return self && self->handler ? UNZ_OK == unzGoToNextFile((unzFile)self->handler) : false;
        }

        bool unz_locate_name(extractor_t *self, std::string filename) {
            return self && self->handler ? UNZ_OK == unzLocateFile((unzFile)self->handler, __exchange_path(filename).c_str(), 0) : false;
        }

        std::unique_ptr<fileinfo_t> unz_info(extractor_t *self, bool isContentRequired, const std::string &password) {
            auto pinfo = std::unique_ptr<fileinfo_t>(new fileinfo_t);
            
            if (!self || !self->handler) return nullptr;
            if (UNZ_OK != unzGetCurrentFileInfo((unzFile)self->handler, (unz_file_info*)pinfo.get(), nullptr, 0, nullptr, 0, nullptr, 0)) return nullptr;

            pinfo->filename.resize(pinfo->filename_size);
            pinfo->comment.resize(pinfo->comment_size);
            if (UNZ_OK != unzGetCurrentFileInfo(
                (unzFile)self->handler, (unz_file_info*)pinfo.get(),
                (char*)pinfo->filename.c_str(), pinfo->filename_size, nullptr, 0,
                (char*)pinfo->comment.c_str(), pinfo->comment_size
            )) return nullptr;
            if (!isContentRequired) return std::move(pinfo);

            // get uncompressed content
            if (UNZ_OK != unzOpenCurrentFile3((unzFile)self->handler, nullptr, nullptr, 0, password.empty() ? nullptr : password.c_str())) return nullptr;
            pinfo->content = io::binary_new(0, pinfo->uncompressed_size);
            if (pinfo->uncompressed_size != unzReadCurrentFile((unzFile)self->handler, (void*)io::binary_addr(pinfo->content.get()), pinfo->uncompressed_size)) {
                unzCloseCurrentFile((unzFile)self->handler);
                return nullptr;
            }
            unzCloseCurrentFile((unzFile)self->handler);
            return std::move(pinfo);
        }

        std::unique_ptr<filepos_t> unz_pos(extractor_t *self) {
            auto dest = std::unique_ptr<filepos_t>(new filepos_t);
            return self && self->handler && UNZ_OK == unzGetFilePos((unzFile)self->handler, (unz_file_pos*)dest.get())
                ? std::move(dest)
                : nullptr;
        }

        bool unz_locate(extractor_t *self, filepos_t *pos) {
            return self && self->handler ? UNZ_OK == unzGoToFilePos((unzFile)self->handler, (unz_file_pos*)pos) : false;
        }

        size_t unz_offset(extractor_t *self) {
            return self && self->handler ? unzGetOffset((unzFile)self->handler) : 0;
        }
    }
}