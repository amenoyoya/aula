#pragma once

#include "sdl/application.hpp"

#ifdef _MSC_VER
    #pragma comment(lib, "libaula_sdl.lib")
    #pragma comment(lib, "SDL2.lib")
    #pragma comment(lib, "SDL2main.lib")
    #pragma comment(lib, "SDL2_ttf.lib")
    #pragma comment(lib, "SDL2_image.lib")

    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "shell32.lib")
    #pragma comment(lib, "shlwapi.lib")
    #pragma comment(lib, "winmm.lib")
    #pragma comment(lib, "imm32.lib")
    #pragma comment(lib, "advapi32.lib")
    #pragma comment(lib, "gdi32.lib")
    #pragma comment(lib, "ole32.lib")
    #pragma comment(lib, "oleaut32.lib")
    #pragma comment(lib, "version.lib")
    #pragma comment(lib, "setupapi.lib")
#endif
