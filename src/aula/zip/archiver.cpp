#include <aula/zip/archiver.hpp>
#include <zlib.h>
#include <zip.h>
#include <unzip.h>

namespace Aula {
    namespace Zip {
        /// ファイルサイズ取得
        static inline u32 getFileSize(const std::string &filename){
            IO::File file(filename, "rb");
            return file.getState() == Object::ACTIVE? file.getSize(): 0;
        }
        
        /// 現在日時取得
        static bool getDate(tm_zip *dest){
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
        
        /// DOS日付を取得
        static inline u16 getDosDate(u32 year, u32 month, u32 day){
            return (u16)(((unsigned)(year - 1980) << 9) | ((unsigned)month << 5) | (unsigned)day);
        }
        
        /// DOS時刻を取得
        static inline u16 getDosTime(u32 hour, u32 minute, u32 second){
            return (u16)(((unsigned)hour << 11) | ((unsigned)minute << 5) | ((unsigned)second >> 1));
        }
        
        /// "\" を "/" に変換
        static inline std::string &exchangePath(std::string &dest){
            for (char *p = (char*)dest.c_str(); *p; ++p) if(*p == '\\') *p = '/';
            return dest;
        }
        
        /*** zlib用ファイル操作関数定義 ***/
        #ifdef _WINDOWS
            #ifdef _MSC_VER
                #define ENCODE(str) Encoding::utf8ToWideString(str).c_str()
                #define _FOPEN(open) _w##open
                #define _STRING(str) L##str
            #else
                #define ENCODE(str) Encoding::utf8ToShiftJIS(str).c_str()
                #define _FOPEN(open) open
                #define _STRING(str) str
            #endif
        #else
            #define ENCODE(str) str
            #define _FOPEN(open) open
            #define _STRING(str) str
        #endif
        #define FOPEN(open, path, mode) _FOPEN(open)(ENCODE(path), mode)
        
        static voidpf ZCALLBACK openFileFunc(voidpf opaque, const char* filename, int mode) {
            FILE *file = nullptr;
            #ifdef _MSC_VER
                const wchar_t* mode_fopen = nullptr;
            #else
                const char* mode_fopen = nullptr;
            #endif
            
            if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER) == ZLIB_FILEFUNC_MODE_READ) mode_fopen = _STRING("rb");
            else if (mode & ZLIB_FILEFUNC_MODE_EXISTING) mode_fopen = _STRING("r+b");
            else if (mode & ZLIB_FILEFUNC_MODE_CREATE) mode_fopen = _STRING("wb");
            
            if (mode_fopen) {
                if (mode_fopen[0] == 'w') IO::createDirectory(Path::getParentDirectory(filename)); // 親ディレクトリ自動生成
                file = FOPEN(fopen, filename, mode_fopen);
            }
            return file;
        }
        
        #undef ENCODE
        #undef _FOPEN
        #undef _STRING
        #undef FOPEN
        
        static uLong ZCALLBACK readFileFunc(voidpf opaque, voidpf stream, void* buf, uLong size) {
            return (uLong)fread(buf, 1, (size_t)size, (FILE *)stream);
        }
        
        static uLong ZCALLBACK writeFileFunc(voidpf opaque, voidpf stream, const void* buf, uLong size) {
            return (uLong)fwrite(buf, 1, (size_t)size, (FILE *)stream);
        }
        
        static long ZCALLBACK tellFileFunc(voidpf opaque, voidpf stream) {
            return ftell((FILE *)stream);
        }
        
        static long ZCALLBACK seekFileFunc(voidpf opaque, voidpf stream, uLong offset, int origin) {
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
            default: return -1;
            }
            
            if (fseek((FILE *)stream, offset, fseek_origin) != 0) ret = -1;
            return ret;
        }
        
        static int ZCALLBACK closeFileFunc(voidpf opaque, voidpf stream) {
            return fclose((FILE *)stream);
        }
        
        static int ZCALLBACK errorFileFunc(voidpf opaque, voidpf stream) {
            return ferror((FILE *)stream);
        }
        
        static zlib_filefunc_def g_fileFuncDef = { // UTF-8対応ファイル操作関数定義
            openFileFunc, readFileFunc, writeFileFunc, tellFileFunc,
            seekFileFunc, closeFileFunc, errorFileFunc, nullptr
        };
        
        
        /*** class Archiver ***/
        bool Archiver::open(const std::string &filename, const std::string &mode, const std::string &password) {
            close();
            
            u8 type;
            if (mode == "w") type = 0;
            else if (mode == "w+") type = 1;
            else if (mode == "a") type = 2;
            else if (mode == "r") type = 3;
            else {
                _state = FAILED;
                _message = "unknown Archiver.open mode";
                return false;
            }

            compressPassword = password; // 圧縮・解凍パスワード
            
            if (type < 3) { // 作成
                if (0 == (zip = (u32)zipOpen2(filename.c_str(), type, nullptr, &g_fileFuncDef))) {
                    _state = FAILED;
                    _message = "failed to create zip file '"+filename+"'";
                    return false;
                }
            } else { // 読み込み
                if (0 == (unz = (u32)unzOpen2(filename.c_str(), &g_fileFuncDef))) {
                    _state = FAILED;
                    _message = "failed to open zip file '"+filename+"'";
                    return false;
                }
                // zipファイル全体のサイズを算出しておく
                u32 offset = getCurrentOffset(), localFileSize = 0; // OFFSET, ローカルファイルサイズの合計
                for (bool flag = toFirstFile(); flag; flag = toNextFile()) {
                    // 各ローカルファイルのヘッダサイズと圧縮サイズ取得
                    auto info = getCurrentFileInformation();
                    if(info == nullptr){
                        _state = FAILED;
                        _message = "failed to get local file information '"+filename+"'";
                        return false;
                    }
                    localFileSize += info->compressedSize + info->fileNameSize + info->fileExtraSize + 30;
                }
                zipSize = (u32)getFileSize(filename) - (offset - localFileSize); // zipサイズ
                if (!toFirstFile()) { // 最初のローカルファイルに戻る
                    _state = FAILED;
                    _message = "failed to go to the first local file '"+filename+"'";
                    return false;
                }
                _state = ACTIVE;
                return true;
            }
            return true;
        }
        
        bool Archiver::close(const std::string &comment) {
            _state = NONE;
            _message.clear();
            if (zip) {
                if (ZIP_OK != zipClose((zipFile)zip, comment != ""?
                    #ifdef _WINDOWS
                        Encoding::utf8ToShiftJIS(comment).c_str()
                    #else
                        comment.c_str()
                    #endif
                    : nullptr)) return false;
                zip = 0;
            }
            if (unz) {
                if (UNZ_OK != unzClose((unzFile)unz)) return false;
                unz = 0;
            }
            return true;
        }
        
        /** zip::Archiver outputモード関数 **/
        bool Archiver::append(const IO::Binary &data, const std::string &destFileName, u32 datasize, const std::string &comment) {
            if (!zip) return false;
            
            zip_fileinfo info;
            std::string name = destFileName;
            
            datasize = datasize == u32(-1)? data.getSize(): datasize;
            getDate(&info.tmz_date);
            info.dosDate = getDosDate(info.tmz_date.tm_year, info.tmz_date.tm_mon, info.tmz_date.tm_mday);
            info.internal_fa = 0;
            info.external_fa = 0;
            // UTF-8対応 flagBase: 1<<11
            if (ZIP_OK != zipOpenNewFileInZip4((zipFile)zip,
                exchangePath(name).c_str(), &info, nullptr, 0,
                nullptr, 0, comment != ""? comment.c_str(): nullptr, Z_DEFLATED, compressLevel,
                0, 15, 8, Z_DEFAULT_STRATEGY, compressPassword != ""? compressPassword.c_str(): nullptr,
                IO::Binary::getCRC32(data, datasize, 0xffffffff), 36, 1 << 11))
            {
                _message = "failed to create local file '"+destFileName+"' in zip";
                return false;
            }
            if (ZIP_OK != zipWriteInFileInZip((zipFile)zip, (const void *)data.getPointer(), datasize)) {
                _message = "failed to write local file '"+destFileName+"' in zip";
                zipCloseFileInZip((zipFile)zip);
                return false;
            }
            zipCloseFileInZip((zipFile)zip);
            return true;
        }
        
        bool Archiver::appendFile(const std::string &srcFileName, const std::string &destFileName, const std::string &comment) {
            if (!zip) return false;
            
            IO::File file(srcFileName, "rb");
            if (file.getState() == FAILED) {
                _message = "failed to read file '"+srcFileName+"'";
                return false;
            }
            
            u32 size = file.getSize();
            auto bin = file.read(size);
            return append(*bin, destFileName, size, comment);
        }
        
        /** zip::Archiver inputモード関数 **/
        std::unique_ptr<GlobalInformation> Archiver::getGlobalInformation() const {
            if (!unz) return nullptr;
            
            unz_global_info info;
            std::unique_ptr<GlobalInformation> dest(new GlobalInformation{});

            if (UNZ_OK != unzGetGlobalInfo((unzFile)unz, &info)) return nullptr;

            dest->entries = info.number_entry;
            dest->commentSize = info.size_comment;
            dest->comment.resize(info.size_comment);
            if (UNZ_OK == unzGetGlobalComment((unzFile)unz, (char*)dest->comment.c_str(), info.size_comment)) return nullptr;
            return std::move(dest);
        }
        
        bool Archiver::toFirstFile() {
            return unz? UNZ_OK == unzGoToFirstFile((unzFile)unz): false;
        }
        
        bool Archiver::toNextFile() {
            return unz? UNZ_OK == unzGoToNextFile((unzFile)unz): false;
        }
        
        bool Archiver::locateFile(std::string filename) {
            return unz? UNZ_OK == unzLocateFile((unzFile)unz, exchangePath(filename).c_str(), 0): false;
        }
        
        std::unique_ptr<FileInformation> Archiver::getCurrentFileInformation(bool getContent) const {
            if (!unz) return nullptr;
            
            unz_file_info info;
            std::unique_ptr<FileInformation> dest(new FileInformation{});

            if (UNZ_OK != unzGetCurrentFileInfo((unzFile)unz, &info, nullptr, 0, nullptr, 0, nullptr, 0)) return nullptr;
            
            memcpy(dest.get(), &info, sizeof(info));
            dest->fileName.resize(info.size_filename);
            dest->comment.resize(info.size_file_comment);

            if (UNZ_OK != unzGetCurrentFileInfo((unzFile)unz, nullptr, (char*)dest->fileName.c_str(), info.size_filename,
                nullptr, 0, (char*)dest->comment.c_str(), info.size_file_comment)) return nullptr;
            
            if (getContent && !readCurrentFileData(&dest->uncompressedData, dest->uncompressedSize)) return nullptr;
            return std::move(dest);
        }
        
        u32 Archiver::getCurrentOffset() const {
            return unz? unzGetOffset((unzFile)unz): 0;
        }
        
        bool Archiver::readCurrentFileData(IO::Binary *dest, u32 size) const {
            if (!unz) return false;
            if (UNZ_OK != unzOpenCurrentFile3((unzFile)unz, nullptr, nullptr, 0, compressPassword != ""? compressPassword.c_str(): nullptr)) return false;

            dest->resize(size);
            unzReadCurrentFile((unzFile)unz, (void *)dest->getPointer(), size);
            unzCloseCurrentFile((unzFile)unz);
            return true;
        }
        
        u8 Archiver::getState() {
            if(unz && 1 == unzeof((unzFile)unz)) return FINISHED;
            else return _state;
        }
    }
}