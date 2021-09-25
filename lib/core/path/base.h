#pragma once

#include "../encoding/base.h"

namespace Aula {
    /// ファイルパスライブラリ
    namespace Path {
        /// ファイル名を抽出
        string getBaseName(const string &path);
        
        /// 拡張子を抜いたファイル名を抽出
        string getBaseStem(const string &path);

        /// 拡張子を抽出
        string getExtension(const string &path);
        
        /// ".."や"."などを上位，カレントディレクトリに変換したパスを取得
        string convert(const string &path);
        
        /// 同一パスかどうか判定
        // len: -1以外を指定するとlenバイト分だけ比較する（-1なら全て比較）
        bool isSame(const string &path1, const string &path2, u32 len=(u32)-1);
        
        /// 親ディレクトリを取得
        // real: trueなら実際の親ディレクトリ, falseなら一番後ろの'/'まで単なる文字列の切り出し
        string getParentDirectory(const string &path, bool real=true);
        
        /// 指定パスがファイルか判定
        bool isFile(const string &path);

        /// 指定パスがディレクトリか判定
        bool isDirectory(const string &path);
        
        /// フルパス取得
        string complete(const string &path);
        
        /// パスの末尾が'/\'でないなら'/\'を末尾に追加
        string appendSlash(const string &path);
        
        /// パスの末尾の'/\'を削除
        string removeSlash(string path);
    }
}