#include "../lib/core.hpp"
#include <iostream>
#include <io.h>
#include <fcntl.h>

#pragma comment(lib, "libaula_core.lib")

__main() {
    Aula::IO::Stdout->write(_U8("あなたの名前は？ > "), false);
    Aula::IO::Stdout->write(Aula::IO::Stdin->readString(256) + _U8(" ですね"));
    return 0;
}