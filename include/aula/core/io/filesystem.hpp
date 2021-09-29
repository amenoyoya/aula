#pragma once

#include "fileenumerator.hpp"

namespace Aula {
    namespace IO {
        /*** ファイル操作関連 ***/

        /// ファイルコピー
        // コピー先のファイルを上書きしたくない場合は overwrite=false にする
        bool copyFile(const std::string &src, const std::string &dest, bool overwrite = true);
        
        /// ファイル削除
        inline bool removeFile(const std::string &file) {
            #ifdef _WINDOWS
                return FALSE != DeleteFileW(Encoding::utf8ToWideString(file).c_str());
            #else
                return 0 == unlink(file.c_str());
            #endif
        }
        
        /// ファイル・ディレクトリの移動(リネーム)
        // destファイルが存在するとき、上書きしたくない場合は overwrite=false にする
        bool moveFile(const std::string &src, const std::string &dest, bool overwrite = true);
        
        
        /*** ディレクトリ操作関連 ***/

        /// ディレクトリ作成
        bool createDirectory(const std::string &dir); // 複数階層のディレクトリ作成可能
        
        /// ディレクトリコピー
        bool copyDirectory(const std::string &src, const std::string &dest);
        
        /// ディレクトリ削除
        bool removeDirectory(const std::string &dir);
        
        /// ディレクトリ移動（コピー＆削除）
        inline bool moveDirectory(const std::string &src, const std::string &dest){
            return copyDirectory(src, dest) && removeDirectory(src);
        }
    }
}
