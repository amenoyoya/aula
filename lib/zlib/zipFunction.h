#pragma once

/*** Zip関連関数 ***/

#include "ZipArchiver.h"

namespace Aula{
    // 埋め込みzipデータを削除する
    bool removeZipData(const string &filename);
    
    // ディレクトリを圧縮する
    // key: zipパスワード
    // level: zip圧縮レベル(0-9)
    // mode: "w"=新規作成, "w+"=埋め込み, "a"=追加
    // rootDir: zip内の仮想ルートディレクトリ名
    bool compressDirectory(const string &dirPath, const string &outputFile,
        const string &key="", u8 level=6, const string &mode="w", const string &rootDir="");
    
    // zipをディレクトリに解凍する
    // key: zipパスワード
    bool uncompressDirectory(const string &zipFile, const string &dirPath, const string &key="");
}
