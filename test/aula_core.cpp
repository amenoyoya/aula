#include "../lib/lua/base.h"

#pragma comment(lib, "libaula_core.lib")
#pragma comment(lib, "libaula_lua.lib")
#pragma comment(lib, "lua51.lib")

__main() {
    sol::state lua;

    // register core libraries
    Aula::Lua::registerCoreLibrary(lua);

    // execute lua script
    Aula::System::setCurrentDirectory(
        Aula::Path::getParentDirectory(Aula::Encoding::toUTF8(argv[0]))
    );
    lua.safe_script_file("aula_core.lua", [](lua_State*, sol::protected_function_result pfr) {
        sol::error err = pfr;
        Aula::IO::Stderr->write(err.what());
        return pfr;
    });
    return 0;
}