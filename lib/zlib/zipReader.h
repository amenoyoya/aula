#pragma once

/* アーカイブファイル操作 */

#include "zipArchiver.h"

namespace Aula{
    /*** ZIPアーカイブ内ファイル読み込みクラス ***/
    class ZipFileReader: public IFileReader {
    public:
        ZipFileReader(): IFileReader(), size(0), cur(0) {}
        explicit ZipFileReader(const string &arcname, const string &filename, const string &password="")
            : IFileReader(), password(password), size(0), cur(0)
        {
            open(arcname, filename);
        }
        ~ZipFileReader(){
            close();
        }
        
        void setPassword(const string &pass){ password = pass; }
        
        bool open(const string &arcname, const string &filename);
        void close(){
            _state = NONE; _message.clear(); bin.clear(); size = cur = 0;
        }
        
        u32 getSize(){ return size; }
        string readLine();
        i8 readChar(){
            return _state == ACTIVE? bin[cur++]: 0;
        }
        u32 read(void *dest, u32 size, u32 n=1);
        string readAll();
        bool seek(i32 move, u8 from=SEEK_SET);
        u32 getPosition(){ return cur; }
    private:
        string    bin,    // ファイル内容をstringで保持
                password;
        u32        size,    // ファイルサイズ
                cur;    // read**, seek用: 現在のポインタ位置
    protected:
        virtual u8 _getState(){ // EOF検知
            return size > 0 && cur >= size? FINISHED: _state;
        }
    };
    
    
    /*** File, ZipFileReaderラッパークラス ***/
    class FileReader: public Object {
    public:
        FileReader(): Object(), pFile(nullptr), arcPathLen(0) {}
        explicit FileReader(const string &filename, const string &ext="", const string &password="")
            : Object(), pFile(nullptr), arcPathLen(0)
        {
            open(filename, ext, password);
        }
        ~FileReader(){
            close();
        }
        
        // openするデフォルトのアーカイブを設定
        void setDefaultArchive(const string &path, const string &key){
            arcPath = path, arcKey = key; arcPathLen = path.size();
        }
        void setDefaultArchive(const FileReader *file){
            arcPath = file->arcPath, arcKey = file->arcKey; arcPathLen = file->arcPathLen;
        }
        
        // File::open, ZipFileReader::open のラッパー
        // "Archive/File"形式のパスをZipFileReaderで開く
        // デフォルトアーカイブが設定されている場合は，まず"DefaultArchive/File"に対するopenを試行(ext, password は無視される)
        // setFileSystemDirectoryで指定したディレクトリ（アーカイブ）も探索する
        // ext: "～ext/"をArchiveと判断してopenを試行
        //         指定しない場合，"/"が見つかる度にZipFileReader::openを試行
        // password: Archiveパスワード
        bool open(const string &filename, const string &ext="", const string &password="");
        
        // File::open
        bool openFile(const string &filename);
        
        // ZipFileReader::open
        bool openFileInZip(const string &arcname, const string &filename, const string &password="");
        
        void close();
        
        // 現在開いているファイルのパス("ディレクトリorアーカイブ/ファイル名")を取得
        const string &getCurrentFilePath() const{return curPath;}
        
        u32 getSize(){
            return (pFile? pFile->getSize(): 0);
        }
        string readLine(){
            return (pFile? pFile->readLine(): "");
        }
        i8 readChar(){
            return (pFile? pFile->readChar(): 0);
        }
        u32 read(void *dest, u32 size, u32 n=1){
            return (pFile? pFile->read(dest, size, n): 0);
        }
        string readAll(){
            return (pFile? pFile->readAll(): "");
        }
        bool seek(i32 move, u8 from=SEEK_SET){
            return (pFile? pFile->seek(move, from): false);
        }
        u32 getPosition(){
            return (pFile? pFile->getPosition(): 0);
        }
    private:
        IFileReader        *pFile; // 条件によってFile,ZipFileReaderクラスに変わる
        string             curPath; // 現在開いているファイルのパス
        
        /* openするデフォルトアーカイブ */
        string arcPath, arcKey;
        u32 arcPathLen;
    protected:
        virtual u8 _getState(){
            return pFile? getState(pFile): _state;
        }
        
        bool __open(const string &filename, const string &ext, const string &password);
    };
}
