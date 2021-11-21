#pragma once

#include "core/os.hpp"
#include "core/filesystem.hpp"

#ifdef _WINDOWS
    #pragma warning(disable:4005)
    
    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "shell32.lib")
    #pragma comment(lib, "shlwapi.lib")
    #pragma comment(lib, "winmm.lib")
#endif

/*** main function macro ***/
#ifdef _WINDOWS
    #define __main() \
    int aula_main(std::vector<std::string> &args);\
    int wmain(int argc, wchar_t **argv) {\
        aula::io::initlocale();\
        std::vector<std::string> args = std::move(aula::os::cmdline(argv, argc));\
        return aula_main(args);\
    }\
    int aula_main(std::vector<std::string> &args)
#else
    #define __main() \
    int aula_main(std::vector<std::string> &args);\
    int main(int argc, char **argv) {\
        aula::io::initlocale();\
        std::vector<std::string> args = std::move(aula::os::cmdline(argv, argc));\
        return aula_main(args);\
    }\
    int aula_main(std::vector<std::string> &args)
#endif

/*** utility macro ***/
#ifdef _WINDOWS
    #define _U8(str) aula::string::wcstou8(L##str)
    #define _S(str) L##str
#else
    #define _U8(str) std::string(str)
    #define _S(str) str
#endif

#define _fputs(fp, str) fputws((aula::string::u8towcs(str) + L"\n").c_str(), fp)
#define _fprintf(fp, format, ...) fwprintf(fp, aula::string::u8towcs(format).c_str(), __VA_ARGS__)

/*** include source files macro ***/
#ifdef _USE_AULA_CORE
    #include "core/io.cpp"
    #include "core/path.cpp"
    #include "core/filesystem.cpp"
#endif
