#include "base.hpp"

namespace Aula {
    namespace Zip {
        bool removeEmbedData(const std::string &filename) {
            Archiver arc(filename, "r");
            if (arc.getState() == Object::FAILED) return false;
            // zip以外の部分のデータをコピー
            IO::File file(filename, "rb");
            u32 size = file.getSize() - arc.getSize();
            auto bin = file.read(size);
            // 上書き
            file.open(filename, "wb");
            return 0 < file.write(*bin, size);
        }
        
        
        /// ディレクトリを圧縮する(基底)
        static bool __compress(Archiver *zip, const std::string &dirPath,
            const std::string &key, u8 level, u32 baseDirLen, const std::string &rootDir)
        {
            IO::FileEnumerator f(dirPath);
            
            if (f.getState() == Object::FAILED) return false;
            do {
                if (f.getName() == "." || f.getName() == "..") continue;
                
                std::string path = f.getPath();

                if (Path::isDirectory(path)) { // ディレクトリは再帰
                    if (!__compress(zip, path, key, level, baseDirLen, rootDir)) return false;
                } else if(Path::isFile(path)) { // ファイルはzipに追加
                    if (!zip->appendFile(path, rootDir + path.substr(baseDirLen), key, level)) return false;
                }
            } while (f.toNext());
            return true;
        }
        
        bool compress(const std::string &dirPath, const std::string &outputFile,
            const std::string &key, u8 level, const std::string &mode, const std::string &rootDir)
        {
            Archiver zip(outputFile, mode);
            
            if (zip.getState() == Object::FAILED) return false;
            return __compress(&zip, dirPath, key, level,
                Path::appendSlash(dirPath).size(), rootDir == ""? "": Path::appendSlash(rootDir));
        }
        
        bool uncompress(const std::string &zipFile, const std::string &dirPath, const std::string &key) {
            Archiver zip(zipFile, "r");
            
            if (zip.getState() == Object::FAILED) return false;
            if (zip.toFirstFile()) return false;
            do {
                IO::File file;
                auto info = zip.getCurrentFileInformation(true, key);

                if (!file.open(Path::appendSlash(dirPath) + info->fileName, "wb")) return false;
                file.write(info->uncompressedData, info->uncompressedData.getSize());
            } while (zip.toNextFile());
            return true;
        }
    }
}
