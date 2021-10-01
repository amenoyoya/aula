﻿#pragma once

#include <aula/core/string/base.hpp>

namespace Aula {
    inline void open_string_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto str = aula["String"].get_or_create<sol::table>();

        str.set_function("isEqualFold", sol::overload(
            [](const std::string &s1, const std::string &s2, u32 len) { return String::isEqualFold(s1, s2, len); },
            [](const std::string &s1, const std::string &s2) { return String::isEqualFold(s1, s2); }
        ));
        str.set_function("replace", String::replace);
    }
}

/*** ffi用export関数 ***/
#ifdef _WINDOWS
extern "C"{
    /* UTF-8 <-> wstring */
    inline __declspec(dllexport) bool utf8ToWideString(const char *source, wchar_t *dest, u32 size) {
        const u8  nMaxReadSize = 6;
        char      chBuffer[nMaxReadSize], *src = (char*)source;
        u32       nReadDataSize = 0, i = 0;
        s32       iCh1, sizeBytes = 0;
        wchar_t   wcWork1 = 0, wcWork2 = 0, wcWork3 = 0;
        // BOMの除去
        if (size > 2 && ((*src == '\xef') && (*(src + 1) == '\xbb') && (*(src + 2) == '\xbf'))) {
            src += 3;
            size -= 3;
        }
        for (u32 cursor = 0; cursor < size;) {
            /* srcより6バイトのデータを読み出し */
            nReadDataSize = (nMaxReadSize < (size - cursor))? nMaxReadSize: (size - cursor);
            memcpy(chBuffer, src + cursor, nReadDataSize);
            memset(chBuffer + nReadDataSize, 0, sizeof(chBuffer) - nReadDataSize);
            /* data size を調べる */
            iCh1 = ((s32)(*chBuffer)) & 0x00ff;
            iCh1 = ~iCh1;    /* ビット反転 */
            if (iCh1 & 0x0080) sizeBytes = 1; /* 0aaabbbb */
            else if (iCh1 & 0x0040) return false; /* error */
            else if (iCh1 & 0x0020) sizeBytes = 2; /* 110aaabb 10bbcccc */
            else if (iCh1 & 0x0010) sizeBytes = 3; /* 1110aaaa 10bbbbcc 10ccdddd */
            else if (iCh1 & 0x0008) sizeBytes = 4; /* 未対応のマッピング(UTF-16に存在しないコード) */
            else if (iCh1 & 0x0004) sizeBytes = 5; /* 未対応のマッピング(UTF-16に存在しないコード) */
            else if (iCh1 & 0x0002) sizeBytes = 6; /* 未対応のマッピング(UTF-16に存在しないコード) */
            else return false; /* error */
            /* sizeBytes毎に処理を分岐 */
            switch (sizeBytes) {
            case 1:
                /*
                * ビット列
                * (0aaabbbb)UTF-8 ... (00000000 0aaabbbb)UTF-16
                */
                dest[i++] = (wchar_t)(chBuffer[0] & (wchar_t)0x00ff);     /* 00000000 0aaabbbb */
                break;
            case 2:
                /*
                * ビット列
                * (110aaabb 10bbcccc)UTF-8 ... (00000aaa bbbbcccc)UTF-16
                */
                wcWork1 = ((wchar_t)(chBuffer[0])) & (wchar_t)0x00ff;   /* 00000000 110aaabb */
                wcWork2 = ((wchar_t)(chBuffer[1])) & (wchar_t)0x00ff;   /* 00000000 10bbcccc */
                wcWork1 <<= 6;                                          /* 00110aaa bb?????? */
                wcWork1 &= 0x07c0;                                      /* 00000aaa bb000000 */
                wcWork2 &= 0x003f;                                      /* 00000000 00bbcccc */
                dest[i++] = wcWork1 | wcWork2;                          /* 00000aaa bbbbcccc */
                break;
            case 3:
                /*
                * ビット列
                * (1110aaaa 10bbbbcc 10ccdddd)UTF-8 ... (aaaabbbb ccccdddd)UTF-16
                */
                wcWork1 = ((wchar_t)(chBuffer[0])) & (wchar_t)0x00ff;   /* 00000000 1110aaaa */
                wcWork2 = ((wchar_t)(chBuffer[1])) & (wchar_t)0x00ff;   /* 00000000 10bbbbcc */
                wcWork3 = ((wchar_t)(chBuffer[2])) & (wchar_t)0x00ff;   /* 00000000 10ccdddd */
                wcWork1 <<= 12;                                         /* aaaa???? ???????? */
                wcWork1 &= 0xf000;                                      /* aaaa0000 00000000 */
                wcWork2 <<= 6;                                          /* 0010bbbb cc?????? */
                wcWork2 &= 0x0fc0;                                      /* 0000bbbb cc000000 */
                wcWork3 &= 0x003f;                                      /* 00000000 00ccdddd */
                dest[i++] = wcWork1 | wcWork2 | wcWork3;                /* aaaabbbb ccccdddd */
                break;
            case 4:
            case 5:
            case 6:
            default:
                /* ダミーデータ(uff1f)を出力 */
                dest[i++] = (wchar_t)0xff1f;
                break;
            }
            cursor += sizeBytes;
        }
        return true;
    }
    
    inline __export bool wideStringToUTF8(const wchar_t *source, char *dest, u32 size) {
        wchar_t   wcWork1 = 0, *src = (wchar_t*)source;
        u32       i = 0;
        s32       sizeBytes = 0;
        char      chWork1 = 0, chWork2 = 0, chWork3 = 0;
        
        for (u32 cursor = 0; cursor < size; ++cursor) {
            /* srcより1ワードのデータを読み出し */
            if (0 == (wcWork1 = *(src + cursor))) return true;
            else if((wcWork1 <= ((wchar_t)0x007f))) sizeBytes = 1; /* 0x0000 to 0x007f */
            else if((((wchar_t)0x0080) <= wcWork1) && (wcWork1 <= ((wchar_t)0x07ff))) sizeBytes = 2; /* 0x0080 to 0x07ff */
            else if((((wchar_t)0x0800) <= wcWork1)) sizeBytes = 3; /* 0x0800 to 0xffff */
            else return false; /* error */
            /* sizeBytes毎に処理を分岐 */
            switch (sizeBytes) {
            case 1:
                /*
                * ビット列
                * (0aaabbbb)UTF-8 ... (00000000 0aaabbbb)UTF-16
                */
                dest[i++] = (char)wcWork1;              /* 0aaabbbb */
                break;
            case 2:
                /*
                * ビット列
                * (110aaabb 10bbcccc)UTF-8 ... (00000aaa bbbbcccc)UTF-16
                */
                chWork1 = (char)(wcWork1 >> 6);     /* 000aaabb */
                chWork1 |= (char)0xc0;              /* 110aaabb */
                chWork2 = (char)wcWork1;            /* bbbbcccc */
                chWork2 &= (char)0x3f;              /* 00bbcccc */
                chWork2 |= (char)0x80;              /* 10bbcccc */
                dest[i++] = chWork1;
                dest[i++] = chWork2;
                break;
            case 3:
                /*
                * ビット列
                * (1110aaaa 10bbbbcc 10ccdddd)UTF-8 ... (aaaabbbb ccccdddd)UTF-16
                */
                chWork1 = (char)(wcWork1 >> 12);    /* ????aaaa */
                chWork1 &= (char)0x0f;              /* 0000aaaa */
                chWork1 |= (char)0xe0;              /* 1110aaaa */
                chWork2 = (char)(wcWork1 >> 6);     /* aabbbbcc */
                chWork2 &= (char)0x3f;              /* 00bbbbcc */
                chWork2 |= (char)0x80;              /* 10bbbbcc */
                chWork3 = (char)wcWork1;            /* ccccdddd */
                chWork3 &= (char)0x3f;              /* 00ccdddd */
                chWork3 |= (char)0x80;              /* 10ccdddd */
                dest[i++] = chWork1;
                dest[i++] = chWork2;
                dest[i++] = chWork3;
                break;
            default:
                break;
            }
        }
        return true;
    }
}
#endif
