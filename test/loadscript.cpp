#include <aula/lua.hpp>

/// Lua script: Compile luasample.lua => bufsample.sym
const char compiler[] = R"(
    local fh, msg = io.open("luasample.lua", "r")

    if not (fh) then
        error(msg)
    end

    local func = assert(load(fh:read"*a", "bufsample.sym"))
    local dump = string.dump(func)

    fh:close()

    -- save
    fh, msg = io.open("bufsample.sym", "wb")

    if not (fh) then
        error(msg)
    end

    fh:write(dump)
    fh:close()
)";

/// Test for sol::state::load_buffer
void testDoScript(sol::state &lua, const std::string &filename) {
    Aula::IO::Stdout->write("\n*** Test: " + filename + " ***");

    Aula::IO::File file(filename, "rb");
    if (file.getState() == Aula::Object::State::FAILED) {
        Aula::IO::Stderr->write("Failed to open: " + filename);
        return;
    }

    auto bin = file.read(file.getSize());
    auto script = lua.load_buffer((const char *)bin->getPointer(), bin->getSize(), filename.c_str());
    if (!script.valid()) {
        sol::error err = script;
        Aula::IO::Stderr->write("File is not a lua script: " + filename);
        return;
    }

    auto result = script();
    if (!result.valid()) {
        sol::error err = result;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
    }
}

__main() {
    sol::state lua;
    std::string dirname = Aula::Path::getParentDirectory(Aula::Path::complete(Aula::Encoding::toUTF8(argv[0])));

    lua.open_libraries(
        sol::lib::base,
        sol::lib::string,
        sol::lib::io,
        sol::lib::debug
    );
    // overload `print` because the process will crash when mixing Aula::IO::Stdout and std::c::print
    lua["print"] = [](const std::string &text) { return Aula::IO::Stdout->write(text); };

    Aula::System::setCurrentDirectory(dirname + "/loadsample");

    /// Preparation: compile ./loadsample/luasample.lua => ./loadsample/bufsample.sym
    lua.safe_script(compiler, [](lua_State*, sol::protected_function_result pfr) {
        sol::error err = pfr;
        Aula::IO::Stderr->write(Aula::Encoding::toUTF8(err.what()));
        return pfr;
    }, "lua byte code compiler");

    /// Test
    testDoScript(lua, "luasample.lua");
    testDoScript(lua, "bufsample.sym");
    testDoScript(lua, "noscript.txt");
    testDoScript(lua, "empty");
    return 0;
}