#include "../lib/lua.hpp"
#include "interception.hpp"

extern "C" {
    #include "interception/library/interception.c"
}

__declspec(dllexport) int luaopen_luaintercept(lua_State *L) {
    sol::state_view lua(L);
}