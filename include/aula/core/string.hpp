#pragma once

#include "config.hpp"
#include <string>
#include <cstring>
#include <sstream>

namespace aula {
    namespace string {
        /// convert UTF-8 string to wide string (UTF-16)
        inline std::wstring u8towcs(const std::string &source) {
            std::wstring        dest;
            const unsigned char nMaxReadSize = 6;
            char                chBuffer[nMaxReadSize], *src = (char*)source.c_str();
            size_t              nReadDataSize = 0, i = 0, size = source.size();
            long                iCh1, sizeBytes = 0;
            wchar_t             wcWork1 = 0, wcWork2 = 0, wcWork3 = 0;
            // allocate destination memory
            dest.resize(size + 1);
            // skip BOM
            if (size > 2 && ((*src == '\xef') && (*(src + 1) == '\xbb') && (*(src + 2) == '\xbf'))) {
                src += 3;
                size -= 3;
            }
            for (size_t cursor = 0; cursor < size;) {
                // read 6 bytes from source string
                nReadDataSize = (nMaxReadSize < (size - cursor))? nMaxReadSize: (size - cursor);
                memcpy(chBuffer, src + cursor, nReadDataSize);
                memset(chBuffer + nReadDataSize, 0, sizeof(chBuffer) - nReadDataSize);
                // investigate data size
                iCh1 = ((long)(*chBuffer)) & 0x00ff;
                iCh1 = ~iCh1; // bit inversion
                if (iCh1 & 0x0080) sizeBytes = 1; /* 0aaabbbb */
                else if (iCh1 & 0x0040) return false; /* error */
                else if (iCh1 & 0x0020) sizeBytes = 2; /* 110aaabb 10bbcccc */
                else if (iCh1 & 0x0010) sizeBytes = 3; /* 1110aaaa 10bbbbcc 10ccdddd */
                else if (iCh1 & 0x0008) sizeBytes = 4; /* no code in UTF-16 */
                else if (iCh1 & 0x0004) sizeBytes = 5; /* no code in UTF-16 */
                else if (iCh1 & 0x0002) sizeBytes = 6; /* no code in UTF-16 */
                else return false; /* error */
                // branch processing by sizeBytes
                switch (sizeBytes) {
                case 1:
                    // bits: (0aaabbbb)UTF-8 ... (00000000 0aaabbbb)UTF-16
                    dest[i++] = (wchar_t)(chBuffer[0] & (wchar_t)0x00ff);   /* 00000000 0aaabbbb */
                    break;
                case 2:
                    // bits: (110aaabb 10bbcccc)UTF-8 ... (00000aaa bbbbcccc)UTF-16
                    wcWork1 = ((wchar_t)(chBuffer[0])) & (wchar_t)0x00ff;   /* 00000000 110aaabb */
                    wcWork2 = ((wchar_t)(chBuffer[1])) & (wchar_t)0x00ff;   /* 00000000 10bbcccc */
                    wcWork1 <<= 6;                                          /* 00110aaa bb?????? */
                    wcWork1 &= 0x07c0;                                      /* 00000aaa bb000000 */
                    wcWork2 &= 0x003f;                                      /* 00000000 00bbcccc */
                    dest[i++] = wcWork1 | wcWork2;                          /* 00000aaa bbbbcccc */
                    break;
                case 3:
                    // bits: (1110aaaa 10bbbbcc 10ccdddd)UTF-8 ... (aaaabbbb ccccdddd)UTF-16
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
                    /* output dummy data (uff1f) */
                    dest[i++] = (wchar_t)0xff1f;
                    break;
                }
                cursor += sizeBytes;
            }
            return dest.c_str();
        }
        
        /// convert wide string (UTF-16) to UTF-8 string
        inline std::string wcstou8(const std::wstring &source) {
            std::string dest;
            wchar_t     wcWork1 = 0, *src = (wchar_t*)source.c_str();
            size_t      i = 0, size = source.size();
            long        sizeBytes = 0;
            char        chWork1 = 0, chWork2 = 0, chWork3 = 0;
            // allocate destination memory
            dest.resize(size * 3 + 1); // max byte is 3 in utf-8
            for (size_t cursor = 0; cursor < size; ++cursor) {
                // read 1 byte data from source string
                if (0 == (wcWork1 = *(src + cursor))) return "";
                else if((wcWork1 <= ((wchar_t)0x007f))) sizeBytes = 1; /* 0x0000 to 0x007f */
                else if((((wchar_t)0x0080) <= wcWork1) && (wcWork1 <= ((wchar_t)0x07ff))) sizeBytes = 2; /* 0x0080 to 0x07ff */
                else if((((wchar_t)0x0800) <= wcWork1)) sizeBytes = 3; /* 0x0800 to 0xffff */
                else return false; /* error */
                // branch processing by sizeBytes
                switch (sizeBytes) {
                case 1:
                    // bits: (0aaabbbb)UTF-8 ... (00000000 0aaabbbb)UTF-16
                    dest[i++] = (char)wcWork1;          /* 0aaabbbb */
                    break;
                case 2:
                    // bits: (110aaabb 10bbcccc)UTF-8 ... (00000aaa bbbbcccc)UTF-16
                    chWork1 = (char)(wcWork1 >> 6);     /* 000aaabb */
                    chWork1 |= (char)0xc0;              /* 110aaabb */
                    chWork2 = (char)wcWork1;            /* bbbbcccc */
                    chWork2 &= (char)0x3f;              /* 00bbcccc */
                    chWork2 |= (char)0x80;              /* 10bbcccc */
                    dest[i++] = chWork1;
                    dest[i++] = chWork2;
                    break;
                case 3:
                    // bits: (1110aaaa 10bbbbcc 10ccdddd)UTF-8 ... (aaaabbbb ccccdddd)UTF-16
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
            return dest.c_str();
        }

        /// convert to UTF-8 string
        inline std::string strtou8(const std::string &source) {
            #ifdef _WINDOWS
                size_t size = MultiByteToWideChar(CP_ACP, 0, source.c_str(), source.size(), nullptr, 0);
                std::wstring wstr(size + 1, L'\0');
                if (!MultiByteToWideChar(CP_ACP, 0, source.c_str(), source.size(), (wchar_t*)wstr.c_str(), size)) return "";
                return std::move(wcstou8(wstr));
            #else
                return source;
            #endif
        }

        /// any type => string
        template<typename T>
        std::string tostr(const T& target, unsigned short precision = 0) {
            std::stringstream ss;
            
            if(precision > 0) ss.precision(precision);
            ss << target;
            return std::move(ss.str());
        }

        /// string => any type
        template<typename T>
        T strto(const std::string &str) {
            T result;
            std::stringstream ss;
            
            ss << str;
            ss >> result;
            return result;
        }
    }
}