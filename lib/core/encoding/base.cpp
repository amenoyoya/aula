#include "base.h"
#include "babel/babel.h"
#include <locale.h>

namespace Aula {
    namespace Encoding{
        void initialize(){
            babel::init_babel();
            setlocale(LC_ALL, "");
        }
        
        string getEncodingName(const string &target){
            return toUTF8(babel::profile_for_UI::get_base_encoding_name(babel::analyze_base_encoding(target)));
        }
        
        /* 指定文字が何バイト文字か判定(戻り値: 1～4, 0=エラー) */
        static u8 getUTF8Byte(u8 c){
            if (c <= 0x7f) return 1;
            else if (c >= 0xc2 && c <= 0xdf) return 2;
            else if (c >= 0xe0 && c <= 0xef) return 3;
            else if (c >= 0xf0 && c <= 0xf7) return 4;
            return 0;
        }
        
        i8 isUTF8(const string &target){
            u8 *p = (u8*)target.c_str();
            // BOM判定
            if (*p == 0xEF && *(p+1) == 0xBB && *(p+2) == 0xBF) return 1;
            // data size を調べる
            while (*p) {
                u8 byte = getUTF8Byte(*p);
                if (byte == 0) return -1;
                p += byte;
            }
            return 0;
        }
        
        string encode(const string &target, u8 toEncoding, u8 fromEncoding) {
            const char *src = target.c_str();
            u32 p = 0;
            // BOMの除去
            if (*src == '\xef' && *(src + 1) == '\xbb' && *(src + 2) == '\xbf') p = 3;
            // エンコーディング
            if (fromEncoding == UNKNOWN) {
                return babel::auto_translate<string>(src + p, toEncoding);
            }
            return babel::manual_translate<string>(src + p, fromEncoding, toEncoding);
        }
        
        string toUTF8(const wstring &target) {
            return babel::manual_translate<wstring>(target, babel::base_encoding::utf16, babel::base_encoding::utf8);
        }
        
        #ifdef _WINDOWS
            string utf8ToShiftJIS(const string &target) {
                const char *src = target.c_str();
                u32 p = 0;
                // BOMの除去
                if (*src == '\xef' && *(src + 1) == '\xbb' && *(src + 2) == '\xbf') p = 3;
                return babel::manual_translate<string, string>(src + p, babel::base_encoding::utf8, babel::base_encoding::sjis);
            }
            
            wstring utf8ToWideString(const string &target) {
                const char *src = target.c_str();
                u32 p = 0;
                // BOMの除去
                if (*src == '\xef' && *(src + 1) == '\xbb' && *(src + 2) == '\xbf') p = 3;
                return babel::manual_translate<string, wstring>(src + p, babel::base_encoding::utf8, babel::base_encoding::utf16);
            }
        #endif
    }
}

#include "babel/babel.cpp"
