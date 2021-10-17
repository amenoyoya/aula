#define SOL_ALL_SAFETIES_ON 1
#define SOL_LUAJIT 1
#include <sol/sol.hpp>
#include <cassert>

int main() {
    sol::state lua;
    int x = 0;

    lua.set_function("beep", [&x]() { x++; });
    lua.set_function("printx", [&x]() { printf("x: %d\n", x); });
    lua.script("beep()");
    assert(x == 1);
    lua.script("printx()");
    return 0;
}