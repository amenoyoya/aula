#pragma once

#include "core.h"

namespace Aula{
    /*** ファイルパスライブラリ ***/
    namespace Path{
        // ファイル名を抽出
        string getLeaf(const string &path);
        // 拡張子を抜いたファイル名を抽出
        string getStem(const string &path);
        // 拡張子を抽出
        string getExtension(const string &path);
        
        // ".."や"."などを上位，カレントディレクトリに変換したパスを取得
        string convert(const string &path);
        
        // 同一パスかどうか判定
        // len: -1以外を指定するとlenバイト分だけ比較する（-1なら全て比較）
        bool isSame(const string &path1, const string &path2, u32 len=(u32)-1);
        
        // 親ディレクトリを取得
        // real: trueなら実際の親ディレクトリ, falseなら一番後ろの'/'まで単なる文字列の切り出し
        string getParent(const string &path, bool real=true);
        
        // ファイルorディレクトリか判定
        bool isFile(const string &path);
        bool isDirectory(const string &path);
        
        // フルパス取得
        string complete(const string &path);
        
        // パスの末尾が'/\'でないなら'/\'を末尾に追加
        string appendSlash(const string &path);
        
        // パスの末尾の'/\'を削除
        string removeSlash(string path);
    }
    
    
    /*** FileReader インターフェイス ***/
    struct IFileReader: public Object {
        IFileReader(): Object() {}
        virtual bool open(const string &path, const string &mode) = 0;
        virtual void close() = 0;
        virtual u32 getSize() = 0;
        virtual string readLine() = 0;
        virtual s8 readChar() = 0;
        virtual u32 read(void *dest, u32 size, u32 n) = 0;
        virtual string readAll() = 0;
        virtual bool seek(s32 move, u8 from) = 0;
        virtual u32 getPosition() = 0;
    };
    
    
    /* ===== Fileクラス(Pipe対応) ===== */
    class File: public IFileReader {
    public:
        File(): IFileReader(), fp(nullptr) {}
        explicit File(const string &path, const string &mode="r"): IFileReader(), fp(nullptr), closeMode(0) {
            open(path, mode);
        }
        explicit File(u32 pFile, u8 closeMode): IFileReader(), fp(nullptr), closeMode(0) {
            open(pFile, closeMode);
        }
        ~File(){
            close();
        }
        
        // 通常のファイルハンドル作成
        // modeの先頭に"p"を付けて指定するとPipeモードで開く: "pw", "pr+" など
        // modeが"w"系のとき，親ディレクトリが存在しないなら自動的につくる
        bool open(const string &path, const string &mode="r");
        // FILE*を直接渡す
        // closeMode: 0=nothing, 1=fclose, 2=pclose
        bool open(u32 pFile, u8 closeMode);
        void close();
        
        u32 getSize();
        
        string readLine();
        s8 readChar(){
            return fp? (s8)fgetc(fp): 0;
        }
        
        bool writeLine(const string &text){
            return fp? EOF != fputs((text + "\n").c_str(), fp): false;
        }
        bool writeChar(s8 c){
            return fp? EOF != fputc(c, fp): false;
        }
        
        /* 以下のread, writeは読み書きした数が返る */
        u32 read(void *dest, u32 size, u32 n=1){
            return fp? fread(dest, size, n, fp): 0;
        }
        u32 write(const char *buf, u32 size=u32(-1), u32 n=1){
            return fp? fwrite(buf, size == u32(-1)? strlen(buf): size, n, fp): 0;
        }
        
        // テキスト読み込み
        string readAll();
        
        bool seek(s32 move=0L, u8 from=SEEK_SET){
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
    
    
    /* ファイル列挙クラス */
    class FileEnumerator: public Object {
    public:
        FileEnumerator(): Object(), handle(0) {}
        explicit FileEnumerator(const string &dir): Object(), handle(0) {
            open(dir);
        }
        ~FileEnumerator(){
            close();
        }
        
        bool open(const string &dir);
        void close();
        
        // 次のファイルへ列挙を進める(falseが返ったら列挙終了)
        // getState(this) == Object::FINISHED でも列挙終了検知可能
        bool toNext();
        
        // ディレクトリ内ファイル名取得
        const string &getName() const{return name;}
        // "ディレクトリ名/ファイル名"取得
        string getPath() const{return dir + name;}
    private:
        u32        handle;
        string    dir, name;
    };
    
    
    /* ファイル操作関連 */
    // コピー先のファイルを上書きしたくない場合はoverwrite=falseにする
    bool copyFile(const string &src, const string &dest, bool overwrite=true);
    
    inline bool removeFile(const string &file){
        #ifdef _WINDOWS
            return FALSE != DeleteFile(Encoding::utf8ToWideString(file).c_str());
        #else
            return 0 == unlink(file.c_str());
        #endif
    }
    
    // ファイル・ディレクトリの移動(リネーム)
    // destファイルが存在するとき、上書きしたくない場合はoverwrite=falseにする
    bool moveFile(const string &src, const string &dest, bool overwrite=true);
    
    
    /* ディレクトリ操作関連 */
    bool createDirectory(const string &dir); // 複数階層のディレクトリ作成可能
    bool copyDirectory(const string &src, const string &dest);
    bool removeDirectory(const string &dir);
    
    inline bool moveDirectory(const string &src, const string &dest){
        return copyDirectory(src, dest) && removeDirectory(src);
    }
}
