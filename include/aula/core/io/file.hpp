#pragma once

#include <aula/core/path/base.hpp>
#include "binary.hpp"
#include <memory>

namespace Aula {
    namespace IO {
        /// class File (Pipe対応)
        // ※ Windows環境では _setmode(_fileno(fp), _O_U16TEXT) で UTF-16 出力を強制する
        class File: public Object {
        public:
            File(): Object(), fp(nullptr) {}
            explicit File(const std::string &path, const std::string &mode = "r"): Object(), fp(nullptr), closeMode(0) {
                open(path, mode);
            }
            explicit File(const void *pFile): Object(), fp(nullptr), closeMode(0) {
                set(pFile);
            }
            ~File(){
                close();
            }
            
            /// ファイルオープン
            // modeの先頭に"p"を付けて指定するとPipeモードで開く: "pw", "pr+" など
            // modeが "w" 系のとき，親ディレクトリが存在しないなら自動的につくる
            bool open(const std::string &path, const std::string &mode = "r");
            
            /// ファイルクローズ
            void close();

            /// ファイルポインタを直接セット
            // 自動クローズは行わない
            void set(const void *pFile);
            
            /// ファイルサイズ取得
            u32 getSize();
            
            /// 一行取得
            std::string readLine();

            /// 指定文字数分の文字列を取得
            // 基本的に標準入力用
            std::string readString(u32 size);

            /// 1byte 取得
            i8 readChar() {
                return fp? (i8)fgetc(fp): 0;
            }
            
            /// バイナリデータ取得
            std::unique_ptr<Binary> read(u32 n, u32 size = 1);

            /// 文字列書き込み
            bool write(const std::string &text, bool appendLF = true) {
                #ifdef _WINDOWS
                    return fp? EOF != fputws(Encoding::utf8ToWideString(text + (appendLF? "\n": "")).c_str(), fp): false;
                #else
                    return fp? EOF != fputs((text + (appendLF? "\n": "")).c_str(), fp): false;
                #endif
            }

            /// バイナリデータ書き込み
            u32 write(const Binary &buf, u32 n = u32(-1), u32 size = 1) {
                return fp? fwrite((const char *)buf.getPointer(), size, n == u32(-1)? buf.getSize(): n, fp): 0;
            }

            /// 1byte 書き込み
            bool writeChar(i8 c) {
                return fp? EOF != fputc(c, fp): false;
            }
            
            /// ファイルポインタ移動
            bool seek(i32 move=0L, u8 from=SeekFrom::HEAD) {
                return fp? fseek(fp, move, from) == 0: false;
            }
            
            /// 現在のファイルポインタ位置
            u32 getPosition() {
                return fp? ftell(fp): 0;
            }
            
            /// バッファを明示的に書き込み
            bool flush() {
                return fp? 0 == fflush(fp): false;
            }

            /// ファイルポインタ取得
            const void *getPointer() const {
                return (const void *)fp;
            }

            /// 状態取得: EOF検知
            virtual u8 getState() const {
                if(fp) return 0 != feof(fp)? FINISHED: _state;
                else return _state;
            }
        private:
            FILE    *fp;
            u8       closeMode;
        };

        /// 標準入出力ファイルポインタ
        // ※ 以下の標準入出力を使う場合、C言語組み込みの printf, scanf 等の標準入出力関数と混在すると落ちるため注意
        extern std::unique_ptr<File> Stdout;
        extern std::unique_ptr<File> Stderr;
        extern std::unique_ptr<File> Stdin;
    }
}