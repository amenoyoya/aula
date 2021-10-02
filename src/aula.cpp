#include <aula/lua.hpp>

/// Aula Engine version
const char version[] = "Aula Engine v.1.0.0";

__main() {
    sol::state lua;

    // コマンドライン引数
    std::vector arguments = Aula::System::getUTF8CommandLineArguments(argv, argc);

    /*
        メインスクリプト
        1. 第1コマンドライン引数: *.lua | *.sym
        2. 実行ファイルと同一ディレクトリにある main.lua | main.sym
            - os.argv[1] に main.lua | main.sym がセットされる
    */
    bool hasMainScript = false;

    if (arguments.size() > 1) {
        std::string ext = Aula::Path::getExtension(arguments[1]);
        if (ext == ".lua" || ext == ".sym") {
            hasMainScript = true;
            arguments[1] = Aula::Path::complete(arguments[1]); // to full path
        }
    }
    if (!hasMainScript) {
        std::string dirname = Aula::Path::appendSlash(Aula::Path::getParentDirectory(arguments[0]));
        if (Aula::Path::isFile(dirname + "main.lua")) {
            hasMainScript = true;
            arguments.insert(arguments.begin() + 1, dirname + "main.lua");
        } else if (Aula::Path::isFile(dirname + "main.sym")) {
            hasMainScript = true;
            arguments.insert(arguments.begin() + 1, dirname + "main.sym");
        }
    }

    // メインスクリプトが指定されていない場合はバージョン表示して終了
    if (!hasMainScript) {
        Aula::IO::Stdout->write(version);
        return 0;
    }

    // register core libraries
    Aula::Lua::registerCoreLibrary(lua);

    // register zip libraries
    Aula::Lua::registerZipLibrary(lua);

    // expand standard libraries
    std::string errorMessage;
    if (!Aula::Lua::expandStandardLibrary(lua, &errorMessage)) {
        Aula::IO::Stderr->write(errorMessage);
        return 1;
    }

    // os.argv[]で引数取得可能に
    auto os = lua["os"].get_or_create<sol::table>();
    os["argv"] = arguments;
    
    // execute lua script
    lua.safe_script_file(arguments[1], [](lua_State*, sol::protected_function_result pfr) {
        sol::error err = pfr;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
        return pfr;
    });
    return 0;
}
