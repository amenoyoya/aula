#include "zipFunction.h"

namespace Aula{
    // 埋め込みzipデータを削除する
    bool removeZipData(const string &filename){
        ZipArchiver arc(filename, "r");
        if(getState(&arc) == Object::FAILED) return false;
        // zip以外の部分のデータをコピー
        File file(filename, "rb");
        u32 size = file.getSize() - arc.getSize();
        string bin;
        bin.resize(size);
        file.read((void*)&bin[0], size);
        // 上書き
        file.open(filename, "wb");
        return 0 < file.write(bin.c_str(), size);
    }
    
    
    // ディレクトリを圧縮する(基底)
    static bool compress(ZipArchiver *zip, const string &dirPath,
        const string &key, u8 level, u32 baseDirLen, const string &rootDir)
    {
        FileEnumerator f(dirPath);
        
        if(getState(&f) == Object::FAILED) return false;
        do{
            if(f.getName() == "." || f.getName() == "..") continue;
            
            string path = f.getPath();
            if(Path::isDirectory(path)){ // ディレクトリは再帰
                if(!compress(zip, path, key, level, baseDirLen, rootDir)) return false;
            }else if(Path::isFile(path)){ // ファイルはzipに追加
                if(!zip->appendFile(rootDir + path.substr(baseDirLen), path, key, level)) return false;
            }
        }while(f.toNext());
        return true;
    }
    
    // ディレクトリを圧縮する
    bool compressDirectory(const string &dirPath, const string &outputFile,
        const string &key, u8 level, const string &mode, const string &rootDir)
    {
        ZipArchiver zip(outputFile, mode);
        
        if(getState(&zip) == Object::FAILED) return false;
        return compress(&zip, dirPath, key, level,
            Path::appendSlash(dirPath).size(), rootDir == ""? "": Path::appendSlash(rootDir));
    }
    
    // zipをディレクトリに解凍する
    bool uncompressDirectory(const string &zipFile, const string &dirPath, const string &key){
        ZipArchiver zip(zipFile, "r");
        
        if(getState(&zip) == Object::FAILED) return false;
        do{
            ZipFileInformation info;
            string data;
            File file;
            
            zip.getCurrentFileInformation(&info);
            data.resize(info.uncompressedSize);
            if(!zip.openReadCurrentFile((void*)&data[0], info.uncompressedSize, key)) return false;
            if(!file.open(Path::appendSlash(dirPath) + info.fileName, "wb")) return false;
            file.write(data.c_str(), info.uncompressedSize);
        }while(zip.toNextFile());
        return true;
    }
}
