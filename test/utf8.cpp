#include "../lib/core.hpp"

#pragma comment(lib, "libaula_core.lib")

__main() {
    // _setmode(_fileno(stdout), _O_U16TEXT) により機種依存文字が出力されるようになっているか確認
    Aula::IO::Stdout->write(_U8("✅ Hello, 世界♥"));
    return 0;
}