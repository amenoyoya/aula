#include "filesystem.h"

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
        
        bool File::open(const std::string &path, const std::string &mode){
            close();
            if(mode[0] == 'p'){
                if(nullptr == (fp = FOPEN(popen, path, mode.substr(1)))){
                    _state = FAILED;
                    _message = "failed to open pipe '"+path+"'";
                    return false;
                }
                closeMode = 2;
            }else{
                if(mode[0] == 'w') createDirectory(Path::getParentDirectory(path)); // 親ディレクトリを自動生成
                if(nullptr == (fp = FOPEN(fopen, path, mode))){
                    _state = FAILED;
                    _message = "failed to open file '"+path+"'";
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

        std::unique_ptr<Binary> File::read(u32 n, u32 size) {
            if (!fp) return nullptr;
            
            Binary *bin = new Binary(size * n);
            u32 readedSize = fread((void *)bin->getPointer(), size, n, fp);

            bin->resize(readedSize);
            return std::unique_ptr<Binary>(bin);
        }


        std::unique_ptr<File> Stdout(new File(stdout));
        std::unique_ptr<File> Stderr(new File(stderr));
        std::unique_ptr<File> Stdin(new File(stdin));
    }
}