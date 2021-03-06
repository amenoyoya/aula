#include <aula/core/io/filesystem.hpp>

namespace Aula {
    namespace IO {
        #ifdef _WINDOWS
            #ifdef _MSC_VER
                #define ENCODE(str) Encoding::utf8ToWideString(str)
                #define _FOPEN(open) _w##open
            #else
                #define ENCODE(str) Encoding::utf8ToShiftJIS(str)
                #define _FOPEN(open) open
            #endif
        #else
            #define ENCODE(str) str
            #define _FOPEN(open) open
        #endif
        #define FOPEN(open, path, mode) _FOPEN(open)(ENCODE(path).c_str(), ENCODE(mode).c_str())

        /// open mode をバイナリモードに強制変更
        static inline std::string toBinaryMode(const std::string &mode) {
            for (char *p = (char *)mode.c_str(); *p; ++p) {
                if (*p == 'b') return mode; // バイナリモードを指定されている場合はそのまま返す
            }
            // バイナリモードを指定されていない場合は "b" を付与
            return mode + "b";
        }
        
        bool File::open(const std::string &path, const std::string &mode){
            close();
            if(mode[0] == 'p'){
                if(nullptr == (fp = FOPEN(popen, path, mode.substr(1)))){
                    _state = FAILED;
                    _message = "failed to open pipe '" + path + "'";
                    return false;
                }
                closeMode = 2;
            } else {
                if (mode[0] == 'w') createDirectory(Path::getParentDirectory(path)); // 親ディレクトリを自動生成
                if (nullptr == (fp = FOPEN(fopen, path, toBinaryMode(mode)))) { // 必ずバイナリモードで開く
                    _state = FAILED;
                    _message = "failed to open file '" + path + "'";
                    return false;
                }
                closeMode = 1;
            }
            _state = ACTIVE;
            return true;
        }
        
        #undef ENCODE
        #undef _FOPEN
        #undef FOPEN
        
        void File::close(){
            _state = NONE;
            _message.clear();
            if (fp) {
                if (closeMode == 1) fclose(fp);
                else if(closeMode == 2)
                    #ifdef _MSC_VER
                        _pclose(fp);
                    #else
                        pclose(fp);
                    #endif
                fp = nullptr;
            }
            closeMode = 0;
        }
        
        std::string File::readLine(){
            if(!fp) return "";
            
            std::string ret;
            ret.reserve(128);
            for(char c = readChar(); c != EOF; c = readChar()){
                if(c == '\r'){
                    readChar(); break; // 次の改行文字を飛ばす
                }else if(c == '\n') break;
                ret.push_back(c);
            }
            return ret;
        }
        
        u32 File::getSize(){
            if(!fp) return 0;
            
            u32 size = 0, current = getPosition();
            seek(0, SEEK_END);
            size = getPosition();
            // 元の位置に戻す
            seek(current, SEEK_SET);
            return size;
        }

        std::string File::readString(u32 size) {
            // 標準入出力であれば fgets
            if (isStdFilePointer(fp)) {
                #ifdef _WINDOWS
                    wchar_t *buffer = new wchar_t[size];
                    std::string result = Encoding::toUTF8(fgetws(buffer, size, fp));

                    delete[] buffer;
                #else
                    char *buffer = new char[size * 4];
                    std::string result = Encoding::toUTF8(fgets(buffer, size * 4, fp));

                    delete[] buffer;
                #endif
                // 改行削除
                result.erase(result.end() - 1);
                return std::move(result);
            }
            // 通常ファイルであれば fread
            return std::move(read(size)->toString());
        }

        std::unique_ptr<Binary> File::read(u32 n, u32 size) {
            if (!fp) return nullptr;
            
            std::unique_ptr<Binary> bin(new Binary(size * n));
            u32 readedSize = fread((void *)bin->getPointer(), size, n, fp);

            bin->resize(readedSize);
            return std::move(bin);
        }


        std::unique_ptr<File> Stdout(new File(stdout));
        std::unique_ptr<File> Stderr(new File(stderr));
        std::unique_ptr<File> Stdin(new File(stdin));
    }
}