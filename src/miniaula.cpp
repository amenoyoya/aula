#include <aula/lua.hpp>

__main() {
    /// Aula Lua Engine 準備
    sol::state lua;
    std::string errorMessage;
    if (!Aula::Lua::registerLibrary(lua, &errorMessage)) {
        Aula::IO::Stderr->write(errorMessage);
        return 1;
    }

    /// コマンドライン引数
    std::vector<std::string> arguments = Aula::System::getUTF8CommandLineArguments(argv, argc);

    // os.argv[]で引数取得可能に
    auto os = lua["os"].get_or_create<sol::table>();
    os["argv"] = sol::as_table(arguments);

    /// main script: os.argv[2].lua
    // * if no os.argv[2], execute as interactive-mode
    // * set package.__chunk, package.__dir
    if (arguments.size() < 2) {
        Aula::Lua::dotty(lua);
        return 0;
    }
    auto package = lua["package"].get_or_create<sol::table>();
    package["__chunk"] = arguments[1];
    package["__dir"] = Aula::Path::getParentDirectory(arguments[1]);
    auto result = lua.safe_script_file(arguments[1]);
    if (result.valid()) return 0;

    sol::error err = result;
    Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
    return 1;
}
