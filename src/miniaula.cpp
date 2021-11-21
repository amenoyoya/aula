#include <aula/lua.hpp>

#ifdef _WINDOWS
    #pragma comment(lib, "libaula.lib")
#endif

__main() {
    /// prepare Aula Lua Engine
    sol::state lua;
    std::string errorMessage;
    if (!aula::lua::openlib(lua, &errorMessage)) {
        _fputs(stderr, errorMessage);
        return 1;
    }

    // os.argv[] <= command line arguments
    auto os = lua["os"].get_or_create<sol::table>();
    os["argv"] = sol::as_table(args);

    /// main script: os.argv[2].lua
    // * if no os.argv[2], execute as interactive-mode
    // * set package.__file, package.__dir
    if (args.size() < 2) {
        aula::lua::dotty(lua);
        return 0;
    }
    auto package = lua["package"].get_or_create<sol::table>();
    package["__file"] = args[1];
    package["__dir"] = aula::path::parentdir(args[1]);
    auto result = lua.safe_script_file(args[1]);
    if (result.valid()) return 0;

    sol::error err = result;
    _fputs(stderr, err.what());
    return 1;
}
