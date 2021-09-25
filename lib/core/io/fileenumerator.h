#pragma once

#include "file.h"

namespace Aula {
    namespace IO {
        /// ファイル列挙クラス
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
            
            /// 次のファイルへ列挙を進める(falseが返ったら列挙終了)
            // getState(this) == Object::FINISHED でも列挙終了検知可能
            bool toNext();
            
            // ディレクトリ内ファイル名取得
            const string &getName() const { return name; }
            // "ディレクトリ名/ファイル名"取得
            string getPath() const { return dir + name; }
        private:
            u32     handle;
            string  dir, name;
        };
    }
}