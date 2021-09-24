#include "../lib/core.h"

#define SOL_ALL_SAFETIMES_ON 1
#include <sol/sol.hpp>

__main() {
    sol::state lua;

    lua.open_libraries(sol::lib::base);

    // namespace
    auto aula = lua["Aula"].get_or_create<sol::table>();
    auto encoding = aula["Encoding"].get_or_create<sol::table>();
    auto console = aula["Console"].get_or_create<sol::table>();
    auto system = aula["System"].get_or_create<sol::table>();
    auto path = aula["Path"].get_or_create<sol::table>();

    // Aula::Encoding library
    encoding.new_enum("Type",
        "UNKNOWN", Aula::Encoding::Type::UNKNOWN,
        "BINARY", Aula::Encoding::Type::BINARY,
        "ANSI", Aula::Encoding::Type::ANSI,
        "SJIS", Aula::Encoding::Type::SJIS,
        "JIS", Aula::Encoding::Type::JIS,
        "EUC", Aula::Encoding::Type::EUC,
        "ISO2022JP", Aula::Encoding::Type::ISO2022JP,
        "UTF8", Aula::Encoding::Type::UTF8,
        "UTF16BE", Aula::Encoding::Type::UTF16BE,
        "UTF16LE", Aula::Encoding::Type::UTF16LE,
        "UTF32BE", Aula::Encoding::Type::UTF32BE,
        "UTF32LE", Aula::Encoding::Type::UTF32LE
    );
    encoding.set_function("getEncodingName", Aula::Encoding::getEncodingName);
    encoding.set_function("isUTF8", Aula::Encoding::isUTF8);
    encoding.set_function("encode", Aula::Encoding::encode);

    // Aula::Console library
    console.set_function("writeLine", Aula::Console::writeLine);
    console.set_function("write", Aula::Console::write);
    console.new_enum("Color",
        "BLACK", Aula::Console::BLACK,
        "BLUE", Aula::Console::BLUE,
        "GREEN", Aula::Console::GREEN,
        "CYAN", Aula::Console::CYAN,
        "RED", Aula::Console::RED,
        "PURPLE", Aula::Console::PURPLE,
        "YELLOW", Aula::Console::YELLOW,
        "WHITE", Aula::Console::WHITE
    );
    console.set_function("setAttribute", Aula::Console::setAttribute);
    console.set_function("setCursorPosition", Aula::Console::setCursorPosition);
    console.set_function("clear", Aula::Console::clear);
    console.set_function("isKeyPressed", Aula::Console::isKeyPressed);
    console.set_function("getPressedKey", Aula::Console::getPressedKey);

    // Aula::System library
    system.set_function("execute", Aula::System::execute);
    system.set_function("sleep", Aula::System::sleep);
    system.set_function("getTime", Aula::System::getTime);
    system.set_function("setEnvironmentVariable", Aula::System::setEnvironmentVariable);
    system.set_function("getEnvironmentVariable", Aula::System::getEnvironmentVariable);
    system.set_function("setCurrentDirectory", Aula::System::setCurrentDirectory);
    system.set_function("getCurrentDirectory", Aula::System::getCurrentDirectory);

    // Aula::Path library
    path.set_function("getLeaf", Aula::Path::getLeaf);
    path.set_function("getStem", Aula::Path::getStem);
    path.set_function("getExtension", Aula::Path::getExtension);
    path.set_function("convert", Aula::Path::convert);
    path.set_function("isSame", Aula::Path::isSame);
    path.set_function("getParentDirectory", Aula::Path::getParentDirectory);
    path.set_function("isFile", Aula::Path::isFile);
    path.set_function("isDirectory", Aula::Path::isDirectory);
    path.set_function("complete", Aula::Path::complete);
    path.set_function("appendSlash", Aula::Path::appendSlash);
    path.set_function("removeSlash", Aula::Path::removeSlash);
    
    // Aula::File class
    auto file = aula.new_usertype<Aula::File>(
        "File",
        sol::constructors<
            Aula::File(),
            Aula::File(const string &, const string &),
            Aula::File(const string &),
            Aula::File(u32, u8)
        >()
    );
    file["open"] = sol::overload(
        static_cast<bool (Aula::File::*)(const string &, const string &)>(&Aula::File::open),
        static_cast<bool (Aula::File::*)(u32, u8)>(&Aula::File::open)
    );
    file["close"] = &Aula::File::close;
    file["getSize"] = &Aula::File::getSize;
    file["readLine"] = &Aula::File::readLine;
    file["readChar"] = &Aula::File::readChar;
    file["writeLine"] = &Aula::File::writeLine;
    file["writeChar"] = &Aula::File::writeChar;
    file["read"] = &Aula::File::read;
    file["write"] = &Aula::File::write;
    file["readAll"] = &Aula::File::readAll;
    file["seek"] = &Aula::File::seek;
    file["getPosition"] = &Aula::File::getPosition;
    file["flush"] = &Aula::File::flush;
    file["getHandle"] = &Aula::File::getHandle;

    // execute lua script
    Aula::System::setCurrentDirectory(
        Aula::Path::getParentDirectory(Aula::Encoding::toUTF8(argv[0]))
    );
    lua.safe_script_file("sol_core.lua", [](lua_State*, sol::protected_function_result pfr) {
        sol::error err = pfr;
        Aula::Console::writeLine(err.what());
        return pfr;
    });
    return 0;
}