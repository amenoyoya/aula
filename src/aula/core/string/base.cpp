#include <aula/core/string/base.hpp>

namespace Aula {
    namespace String {
        bool isEqualFold(const std::string &s1, const std::string &s2, u32 len) {
            unsigned char *p1 = (unsigned char*)s1.c_str(), *p2 = (unsigned char*)s2.c_str();
            u32 i = 0;
            
            while (*p1 || *p2) {
                if (len != (u32)-1 && len == i) return true;
                if (toupper(*p1) != toupper(*p2)) return false;
                ++p1;
                ++p2;
                ++i;
            }
            return true;
        }
        
        std::string replace(std::string str, const std::string &oldString, const std::string &newString){
            size_t p = str.find(oldString);
            const size_t oldStringLength = oldString.length(), newStringLength = newString.length();
            
            while(p != std::string::npos){
                str.replace(p, oldStringLength, newString);
                p = str.find(oldString, p + newStringLength);
            }
            return std::move(str);
        }
    }
}
