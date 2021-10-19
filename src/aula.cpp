#include <aula/lua.hpp>
#include <map>

__main() {
    /// Aula Engine version
    const char version[] =
        "Aula Engine v.1.1.1 -- Copyright (C) 2021 amenoyoya. https://github.com/amenoyoya/aula\n"
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

    /// CLI commands
    std::map<std::string, std::function<int()>> commands = {
        {
            // print help
            "help", []() {
                Aula::IO::Stdout->write(
                    "Aula is a lua script engine.\n"
                    "\n"
                    "Usage:\n\taula [command] [script_file] [arguments]\n"
                    "\n"
                    "The commands are:\n"
                    "\thelp\tdisplay information about Aula script engine\n"
                    "\tversion\tdisplay Aula version\n"
                    "\ttest\texecute test codes\n"
                    "\t\tUsage:\taula test [directory (default: ./)]\n"
                    "\t\tDescription:\tAula will execute test script files like \"*_test.lua\" in the target directory and the sub directories\n"
                    "\n"
                    "The script file will be executed:\n"
                    "\tIf the command line arguments[1] is \"*.lua\" file (Plain lua source code file)\n"
                    "\tOr if the command line arguments[1] is \"*.sym\" file (Compiled lua byte code file)\n"
                    "\tOr if the \"main.lua\" file exists at the directory containing Aula\n"
                    "\tOr if the \"main.sym\" file exists at the directory containing Aula\n"
                    "\n"
                    "Aula will be executed as interactive-mode if there are no commands and script files.\n"
                );
                return 0;
            }
        }, {
            // print version
            "version", [&version]() {
                Aula::IO::Stdout->write(version);
                return 0;
            }
        }, {
            // execute tests
            "test", [&lua, &arguments]() {
                // 指定ディレクトリ or カレントディレクトリ配下（サブディレクトリ含む）の "*_test.lua" を実行して実行時間計測
                auto files = Aula::IO::enumerateFiles(arguments.size() > 2 ? arguments[2] : ".", -1, Aula::IO::EnumFileOption::FILE);
                const char compareStr[] = "_test.lua";
                u32 compareSize = strlen(compareStr);
                u32 cntOK = 0, cntNG = 0; // テスト結果カウント
                u32 testStart = Aula::System::getTime(); // テスト実行時間計測

                for (auto file = files.begin(); file != files.end(); ++file) {
                    if (file->path.size() < compareSize || file->path.substr(file->path.size() - compareSize) != compareStr) continue;
                    
                    // test code 実行時間計測
                    u32 start = Aula::System::getTime();
                    auto result = lua.safe_script_file(file->path);

                    if (result.valid()) { // OK
                        Aula::IO::Stdout->write(_U8("✅ ") + file->path + " (" + Aula::Encoding::toString(Aula::System::getTime() - start) + " ms)");
                        cntOK++;
                    } else { // NG
                        sol::error err = result;
                        Aula::IO::Stdout->write(_U8("❌ ") + file->path + " (" + Aula::Encoding::toString(Aula::System::getTime() - start) + " ms)");
                        Aula::IO::Stdout->write(Aula::Encoding::toUTF8(err.what()));
                        cntNG++;
                    }
                }
                // display test summary
                Aula::IO::Stdout->write("\nTests:\t" + Aula::Encoding::toString(cntNG) + " failed, " + Aula::Encoding::toString(cntNG + cntOK) + " total");
                Aula::IO::Stdout->write("Time:\t" + Aula::Encoding::toString(Aula::System::getTime() - testStart) + " ms");
                return 0;
            }
        },
    };

    /*
        メインスクリプト
        1. 第1コマンドライン引数: *.lua | *.sym
        2. 実行ファイルと同一ディレクトリにある main.lua | main.sym
            - os.argv[1] に main.lua | main.sym がセットされる
    */
    bool hasMainScript = false;

    if (arguments.size() > 1) {
        // built-in command が指定されている場合
        auto command = commands.find(arguments[1]);
        if (command != commands.end()) {
            return command->second();
        }

        // Lua script file が渡されている場合
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

    // メインスクリプトが指定されていない場合はバージョン表示して interactive mode で起動
    if (!hasMainScript) {
        Aula::IO::Stdout->write(version);
        Aula::Lua::dotty(lua);
        return 0;
    }
    
    // execute lua script
    lua.safe_script_file(arguments[1], [](lua_State*, sol::protected_function_result pfr) {
        sol::error err = pfr;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
        return pfr;
    });
    return 0;
}
