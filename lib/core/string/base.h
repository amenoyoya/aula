#pragma once

/*** C++ Aula library の内部文字エンコーディングはUTF-8で統一 ***/

#include "../object/object.h"

namespace Aula {
    namespace String {
        /// 任意型 => 文字列変換
        // precision: 浮動小数点数などの精度。デフォルトは6
        template<typename T>
        string toString(const T& target, u8 precision=0){
            stringstream ss;
            
            if(precision > 0) ss.precision(precision);
            ss<<target;
            return ss.str();
        }
        
        /// 文字列 => 任意型変換
        template<typename T>
        T stringTo(const string &str){
            T result;
            stringstream ss;
            
            ss<<str;
            ss>>result;
            return result;
        }
        
        /// 大文字へ変換
        inline void toUpper(const string::iterator &begin, const string::iterator &end){
            for(string::iterator it = begin; it != end; ++it) (*it) = (i8)::toupper(*it);
        }
        
        /// 小文字へ変換
        inline void toLower(const string::iterator &begin, const string::iterator &end){
            for(string::iterator it = begin; it != end; ++it) (*it) = (i8)::tolower(*it);
        }
        
        /// 大文字・小文字を区別せずに文字列を比較し、一致するか判定
        // len: -1以外を指定するとlenバイト分だけ比較する（-1なら全て比較）
        bool isEqualFold(const string &s1, const string &s2, u32 len=(u32)-1);
        
        /// 文字列を全置換する
        string replace(string str, const string &oldString, const string &newString);
    }
}
