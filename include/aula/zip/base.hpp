#pragma once

/*** Zip関連関数 ***/

#include "archiver.hpp"

namespace Aula {
    namespace Zip {
        /// 埋め込みzipデータを削除する
        bool removeEmbedData(const std::string &filename);
        
        /// ディレクトリを圧縮する
        // @param key: zipパスワード
        // @param level: zip圧縮レベル(0-9)
        // @param mode: "w"=新規作成, "w+"=埋め込み, "a"=追加
        // @param rootDir: zip内の仮想ルートディレクトリ名
        bool compress(const std::string &dirPath, const std::string &outputFile,
            const std::string &key="", u8 level=6, const std::string &mode="w", const std::string &rootDir="");
        
        /// zipをディレクトリに解凍する
        // @param key: zipパスワード
        bool uncompress(const std::string &zipFile, const std::string &dirPath, const std::string &key="");
    }
}
