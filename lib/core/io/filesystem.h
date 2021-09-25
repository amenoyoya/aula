#pragma once

#include "fileenumerator.h"

namespace Aula {
    namespace IO {
        /*** ファイル操作関連 ***/

        /// ファイルコピー
        // コピー先のファイルを上書きしたくない場合は overwrite=false にする
        bool copyFile(const string &src, const string &dest, bool overwrite = true);
        
        /// ファイル削除
        inline bool removeFile(const string &file) {
            #ifdef _WINDOWS
                return FALSE != DeleteFile(Encoding::utf8ToWideString(file).c_str());
            #else
                return 0 == unlink(file.c_str());
            #endif
        }
        
        /// ファイル・ディレクトリの移動(リネーム)
        // destファイルが存在するとき、上書きしたくない場合は overwrite=false にする
        bool moveFile(const string &src, const string &dest, bool overwrite = true);
        
        
        /*** ディレクトリ操作関連 ***/

        /// ディレクトリ作成
        bool createDirectory(const string &dir); // 複数階層のディレクトリ作成可能
        
        /// ディレクトリコピー
        bool copyDirectory(const string &src, const string &dest);
        
        /// ディレクトリ削除
        bool removeDirectory(const string &dir);
        
        /// ディレクトリ移動（コピー＆削除）
        inline bool moveDirectory(const string &src, const string &dest){
            return copyDirectory(src, dest) && removeDirectory(src);
        }
    }
}
