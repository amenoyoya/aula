#pragma once

#include "../string/base.h"

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
            return isUTF8(target) == -1? encode(target, UTF8, fromEncoding): target;
        }
        std::string toUTF8(const std::wstring &target);
        
        #define _U8(str) Aula::Encoding::toUTF8(L##str)
        
        #ifdef _WINDOWS
            // 対象文字列をUTF-8からShift-JISにエンコーディング
            std::string utf8ToShiftJIS(const std::string &target);
            
            // UTF-8 -> wstring
            std::wstring utf8ToWideString(const std::string &target);
        #endif
    }
}
