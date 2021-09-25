#pragma once

#include "file.h"

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
    }
}