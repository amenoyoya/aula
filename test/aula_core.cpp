#include "../lib/lua.hpp"

__main() {
    sol::state lua;
    std::string errorMessage;

    // register core libraries
    Aula::Lua::registerCoreLibrary(lua);

    // register zip libraries
    Aula::Lua::registerZipLibrary(lua);

    // expand standard libraries
    if (!Aula::Lua::expandStandardLibrary(lua, &errorMessage)) {
        Aula::IO::Stderr->write(errorMessage);
        return 1;
    }

    // execute lua script
    Aula::System::setCurrentDirectory(
        Aula::Path::getParentDirectory(Aula::Encoding::toUTF8(argv[0]))
    );
    lua.safe_script_file("aula_core.lua", [](lua_State*, sol::protected_function_result pfr) {
        sol::error err = pfr;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
        return pfr;
    });
    return 0;
}