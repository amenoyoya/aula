#pragma once

#include "lua/aula.hpp"

#ifdef _WINDOWS
    #pragma comment(lib, "lua51.lib")
#endif

/*** include source files macro ***/
#ifdef _USE_AULA_LUA
    #include "lua/openlib.cpp"
    #include "lua/dotty.cpp"
#endif
