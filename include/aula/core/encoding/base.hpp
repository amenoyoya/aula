#pragma once

/*** 内部文字エンコーディングは UTF-8 で統一 ***/

#include "../base/object.hpp"

namespace Aula {
    /// 文字列エンコーディング関連
    namespace Encoding {
        /// エンコーディングタイプ
        enum Type {
            UNKNOWN,
            BINARY,
            ANSI,
            SJIS,
            JIS,
            EUC,
            ISO2022JP,
            UTF8,
            UTF16BE,
            UTF16LE,
            UTF32BE,
            UTF32LE
        };
        
        /// エンコーディングエンジン初期化
        // この関数を最初に必ず呼び出すこと
        void initialize();
        
        /// 対象文字列のエンコーディング名取得
        std::string getEncodingName(const std::string &target);
        
        /// UTF-8文字列か判定(0=YES, 1=BOM付, -1=NO)
        i8 isUTF8(const std::string &target);
        
        /// 対象文字列を任意のフォーマットにエンコード
        // fromEncoding: 対象文字列のエンコーディングタイプ。ENC_UNKNOWNなら自動判別
        std::string encode(const std::string &target, u8 toEncoding, u8 fromEncoding = UNKNOWN);
        
        /// 対象文字列をUTF-8にエンコーディング
        // fromEncoding: 対象文字列のエンコーディングタイプ。ENC_UNKNOWNなら自動判別
        inline std::string toUTF8(const std::string &target, u8 fromEncoding = UNKNOWN){
            return isUTF8(target) == -1? std::move(encode(target, UTF8, fromEncoding)): std::move(target);
        }
        std::string toUTF8(const std::wstring &target);
        
        #ifdef _WINDOWS
            #define _U8(str) Aula::Encoding::toUTF8(L##str)
        #else
            #define _U8(str) std::string(str)
        #endif
        
        #ifdef _WINDOWS
            // 対象文字列をUTF-8からShift-JISにエンコーディング
            std::string utf8ToShiftJIS(const std::string &target);
            
            // UTF-8 -> wstring
            std::wstring utf8ToWideString(const std::string &target);
        #endif


        /// 任意型 => 文字列変換
        // precision: 浮動小数点数などの精度。デフォルトは6
        template<typename T>
        std::string toString(const T& target, u8 precision=0){
            std::stringstream ss;
            
            if(precision > 0) ss.precision(precision);
            ss << target;
            return std::move(ss.str());
        }
        
        /// 文字列 => 任意型変換
        template<typename T>
        T stringTo(const std::string &str){
            T result;
            std::stringstream ss;
            
            ss << str;
            ss >> result;
            return result;
        }
        
        /// 大文字へ変換
        inline void toUpper(const std::string::iterator &begin, const std::string::iterator &end){
            for(std::string::iterator it = begin; it != end; ++it) (*it) = (i8)::toupper(*it);
        }
        
        /// 小文字へ変換
        inline void toLower(const std::string::iterator &begin, const std::string::iterator &end){
            for(std::string::iterator it = begin; it != end; ++it) (*it) = (i8)::tolower(*it);
        }
        
        /// 文字列比較
        // @param compareCase (default: true): false にすると大文字・小文字の区別をしない
        // @param len: -1以外を指定するとlenバイト分だけ比較する（-1なら全て比較）
        bool isSameString(const std::string &s1, const std::string &s2, bool compareCase = true, u32 len = (u32)-1);
        
        /// 文字列を全置換する
        std::string replaceString(std::string str, const std::string &oldString, const std::string &newString);
    }
}
