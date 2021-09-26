#pragma once

// ライブラリリンク
#ifdef _MSC_VER
    #pragma warning(disable:4005)
    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "shell32.lib")
    #pragma comment(lib, "shlwapi.lib")
    #pragma comment(lib, "winmm.lib")
#endif

#include "core/io/filesystem.hpp"
#include "core/system/base.hpp"

/*** アプリケーションMain関数マクロ ***/
#ifdef _WINDOWS
    #define __main() \
    int Aula_main(int, wchar_t**);\
    int wmain(int argc, wchar_t **argv){\
        Aula::Encoding::initialize();\
        return Aula_main(argc, argv);\
    }\
    int Aula_main(int argc, wchar_t **argv)
    
    
    #define __WinMain() \
    int Aula_main(HINSTANCE, HINSTANCE, LPWSTR , int);\
    int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdLine){\
        Aula::Encoding::initialize();\
        return Aula_main(hInstance, hPrevInstance, lpCmdLine, nCmdLine);\
    }\
    int Aula_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdLine)
#else
    #define __main() \
    int Aula_main(int, char**);\
    int main(int argc, char **argv){\
        Aula::Encoding::initialize();\
        return Aula_main(argc, argv);\
    }\
    int Aula_main(int argc, char **argv)
#endif
