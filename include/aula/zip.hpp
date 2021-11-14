#pragma once

#include "zip/utility.hpp"

#ifdef _WINDOWS
    #pragma comment(lib, "zlib.lib")
#endif

/*** include source files macro ***/
#ifdef _USE_AULA_ZIP
    #include "zip/archiver.cpp"
    #include "zip/utility.cpp"
#endif
