#include <aula/lua.hpp>
#include <map>

__main() {
    /// Aula Engine version
    const char version[] =
        "Aula Engine v.1.2.0 -- Copyright (C) 2021 amenoyoya. https://github.com/amenoyoya/aula\n"
        "LuaJIT 2.1.0-beta3 -- Copyright (C) 2005-2017 Mike Pall. http://luajit.org/";

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

    // main script: 実行ファイルのリソースzipデータから main.sym を読み込んで実行する
    Aula::Zip::Archiver arc(arguments[0], "r");

    if (arc.getState() == Aula::Object::State::FAILED) {
        Aula::IO::Stderr->write(arc.getMessage());
        return 1;
    }
    if (!arc.locateFile("main.sym")) {
        Aula::IO::Stderr->write("no main script found in \"" + arguments[0] + "\"");
        return 1;
    }

    auto mainScript = arc.getCurrentFileInformation(true);
    auto script = lua.load_buffer(
        (const char *)mainScript->uncompressedData.getPointer(),
        mainScript->uncompressedData.getSize(),
        "@" + arguments[0]
    );
    
    if (!script.valid()) {
        sol::error err = script;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
        return 1;
    }

    auto result = script();
    if (!result.valid()) {
        sol::error err = result;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
        return 1;
    }
    return 0;
}
