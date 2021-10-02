#pragma once

#include "file.hpp"
#include <vector>

namespace Aula {
    namespace IO {
        /// ファイル列挙クラス
        class FileEnumerator: public Object {
        public:
            FileEnumerator(): Object(), handle(0) {}
            explicit FileEnumerator(const std::string &dir): Object(), handle(0) {
                open(dir);
            }
            ~FileEnumerator(){
                close();
            }
            
            bool open(const std::string &dir);
            void close();
            
            /// 次のファイルへ列挙を進める(falseが返ったら列挙終了)
            // this->getState() == Object::FINISHED でも列挙終了検知可能
            bool toNext();
            
            // ディレクトリ内ファイル名取得
            const std::string &getName() const { return name; }
            // "ディレクトリ名/ファイル名"取得
            std::string getPath() const { return dir + name; }
        private:
            u32          handle;
            std::string  dir, name;
        };


        /// ファイル列挙オプション
        enum EnumFileOption {
            DIR = 0, // ディレクトリのみ
            FILE,    // ファイルのみ
            ALL,     // 全て
        };

        /// ファイル情報構造体
        struct FileInfo {
            std::string path;
            bool        isFile, isDirectory;
        };

        /// ディレクトリ内ファイル列挙
        // @param dir: 対象ディレクトリ
        // @param nest: 列挙深度(0なら列挙しない，マイナスなら無制限)
        // @param opt: 列挙オプション(2=全て列挙，1=ファイルのみ列挙，0=ディレクトリのみ列挙)
        std::vector<FileInfo> enumerateFiles(const std::string &dir, i32 nest = -1, EnumFileOption opt = ALL);
    }
}