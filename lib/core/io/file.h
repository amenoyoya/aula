#pragma once

#include "../path/base.h"
#include "binary.h"
#include <memory>

namespace Aula {
    namespace IO {
        /// interface FileReader
        struct IFileReader: public Object {
            IFileReader(): Object() {}
            virtual bool open(const string &path, const string &mode) = 0;
            virtual void close() = 0;
            virtual u32 getSize() = 0;
            virtual string readLine() = 0;
            virtual i8 readChar() = 0;
            virtual unique_ptr<Binary> read(u32 size, u32 n) = 0;
            virtual string readAll() = 0;
            virtual bool seek(i32 move, u8 from) = 0;
            virtual u32 getPosition() = 0;
        };
        
        
        /// class File (Pipe対応)
        class File: public IFileReader {
        public:
            File(): IFileReader(), fp(nullptr) {}
            explicit File(const string &path, const string &mode="r"): IFileReader(), fp(nullptr), closeMode(0) {
                open(path, mode);
            }
            ~File(){
                close();
            }
            
            /// ファイルオープン
            // modeの先頭に"p"を付けて指定するとPipeモードで開く: "pw", "pr+" など
            // modeが "w" 系のとき，親ディレクトリが存在しないなら自動的につくる
            bool open(const string &path, const string &mode="r");
            
            /// ファイルクローズ
            void close();
            
            /// ファイルサイズ取得
            u32 getSize();
            
            /// 一行取得
            string readLine();

            /// 1byte 取得
            i8 readChar(){
                return fp? (i8)fgetc(fp): 0;
            }
            
            /// 一行書き込み
            bool writeLine(const string &text){
                return fp? EOF != fputs((text + "\n").c_str(), fp): false;
            }

            /// 1byte 書き込み
            bool writeChar(i8 c){
                return fp? EOF != fputc(c, fp): false;
            }
            
            /// バイナリデータ取得
            unique_ptr<Binary> read(u32 size, u32 n=1);

            /// バイナリデータ書き込み
            u32 write(const char *buf, u32 size=u32(-1), u32 n=1){
                return fp? fwrite(buf, size == u32(-1)? strlen(buf): size, n, fp): 0;
            }
            
            /// テキスト全文取得
            string readAll();
            
            /// ファイルポインタ移動
            bool seek(i32 move=0L, u8 from=SeekFrom::HEAD){
                return fp? fseek(fp, move, from) == 0: false;
            }
            
            // 現在のファイルポインタ位置
            u32 getPosition(){
                return fp? ftell(fp): 0;
            }
            
            // バッファを明示的に書き込み
            bool flush(){
                return fp? 0 == fflush(fp): false;
            }
            
            FILE *getHandle(){return fp;}
        private:
            FILE    *fp;
            u8         closeMode;
        protected:
            virtual u8 _getState(){ // EOF検知
                if(fp) return 0 != feof(fp)? FINISHED: _state;
                else return _state;
            }
        };
    }
}