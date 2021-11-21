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

    // main script: main.sym in zip resource of this execution file
    auto unz = aula::zip::unz_open(args[0]);
    if (!unz) {
        _fputs(stderr, "no resource: " + args[0]);
        return 1;
    }
    if (!aula::zip::unz_locate_name(unz.get(), "main.sym")) {
        _fputs(stderr, "no main script: " + args[0]);
        return 1;
    }

    auto info = aula::zip::unz_info(unz.get(), true);
    if (!info) {
        _fputs(stderr, "cannot extract main script: " + args[0]);
        return 1;
    }

    auto script = lua.load_buffer((const char*)info->content->head, info->uncompressed_size, "@" + args[0]);
    if (!script.valid()) {
        sol::error err = script;
        _fputs(stderr, err.what());
        return 1;
    }

    auto result = script();
    if (!result.valid()) {
        sol::error err = result;
        _fputs(stderr, err.what());
        return 1;
    }
    return 0;
}
