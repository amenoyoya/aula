#include "aula.hpp"
#include "glue/core.hpp"
#include "glue/zip.hpp"

#include "luautf8/lutf8lib.c"
#include "lpeg-1.0.0/lpcap.c"
#include "lpeg-1.0.0/lpcode.c"
#include "lpeg-1.0.0/lpprint.c"
#include "lpeg-1.0.0/lptree.c"
#include "lpeg-1.0.0/lpvm.c"

/* Lua extended standard libraries */
static unsigned char core_lib_code[] = {
    #include "stdlib/core.cpp"
}, table_lib_code[] = {
    #include "stdlib/table.cpp"
}, string_lib_code[] = {
    #include "stdlib/string.cpp"
}, lpeg_lib_code[] = {
    #include "stdlib/lpeg.cpp"
};

/// @private execute lua byte-code
static bool exec_lua_buffer(sol::state &lua, const char *buffer, size_t bufferSize, const std::string &scriptName, std::string *errorMessage) {
    auto script = lua.load_buffer(buffer, bufferSize, scriptName.c_str());
    if (!script.valid()) {
        sol::error err = script;
        *errorMessage = std::move(err.what());
        return false;
    }

    auto result = script();
    if (!result.valid()) {
        sol::error err = result;
        *errorMessage = std::move(err.what());
        return false;
    }
    return true;
}

/// @private register lua extended standard libraries
static bool regist_lua_stdlib(sol::state &lua, std::string *errorMessage) {
    /// register glue codes
    aula::core::openlib(lua);
    aula::zip::openlib(lua);

    /// oberload `debug.debug()`: call lua_dotty
    auto debug = lua["debug"].get_or_create<sol::table>();
    debug["debug"].set_function(sol::overload(
        [&lua](const std::string &progname) { aula::lua::dotty(lua, progname); },
        [&lua]() { aula::lua::dotty(lua); }
    ));

    if (!exec_lua_buffer(lua, (const char *)core_lib_code, sizeof(core_lib_code), "@stdlib://core", errorMessage)) return false;
    if (!exec_lua_buffer(lua, (const char *)table_lib_code, sizeof(table_lib_code), "@stdlib://table", errorMessage)) return false;
    if (!exec_lua_buffer(lua, (const char *)string_lib_code, sizeof(string_lib_code), "@stdlib://string", errorMessage)) return false;
    if (!exec_lua_buffer(lua, (const char *)lpeg_lib_code, sizeof(lpeg_lib_code), "@stdlib://lpeg", errorMessage)) return false;
    return true;
}

namespace aula {
    namespace lua {
        bool openlib(sol::state &lua, std::string *errorMessage) {
            lua.open_libraries(
                sol::lib::base,
                sol::lib::coroutine,
                sol::lib::package,
                sol::lib::string,
                sol::lib::table,
                sol::lib::io,
                sol::lib::math,
                sol::lib::os,
                sol::lib::debug,
                sol::lib::ffi,
                sol::lib::bit32,
                sol::lib::jit
            );
            // UTF-8 support
            luaopen_utf8(lua);
            lua_setglobal(lua, "utf8"); // set to global `utf8` table
            // LPEG support
            luaopen_lpeg(lua); // to use `require"ffi"`
            // register lua extended standard libraries
            return regist_lua_stdlib(lua, errorMessage);
        }
    }
}