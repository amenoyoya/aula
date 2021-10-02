#pragma once

#include <aula/core/system/base.hpp>

namespace Aula {
    /*
    /// loadstring: lua script loader
    // @retuns (chunk::function, error::string)
    inline std::tuple<sol::object, sol::object> loadstring(sol::state &lua, const std::string &script, const std::string &chunkname = "<string>") {
        auto func = lua.load_buffer(script.c_str(), script.size(), chunkname.c_str());
        if (!func.valid()) {
            sol::error err = func;
            return std::make_tuple(sol::nil, sol::make_object(lua, Encoding::toUTF8(err.what())));
        }
        return std::make_tuple((sol::function)func, sol::nil);
    }

    /// loadbuffer: lua byte code loader
    // @retuns (chunk::function, error::string)
    inline std::tuple<sol::object, sol::object> loadbuffer(sol::state &lua, Aula::IO::Binary *buffer, u32 buffersize = u32(-1), const std::string &chunkname = "<string>") {
        auto func = lua.load_buffer((const char *)buffer->getPointer(), buffersize == u32(-1) ? buffer->getSize() : buffersize, chunkname.c_str());
        if (!func.valid()) {
            sol::error err = func;
            return std::make_tuple(sol::nil, sol::make_object(lua, Encoding::toUTF8(err.what())));
        }
        return std::make_tuple((sol::function)func, sol::nil);
    }
    */

    inline void open_system_library(sol::state &lua) {
        /// Aula::System::* は Lua 標準 os.* パッケージに統合
        auto os = lua["os"].get_or_create<sol::table>();

        os.set_function("execute", System::execute);
        os.set_function("sleep", System::sleep);
        os.set_function("systime", System::getTime);
        os.set_function("setenv", System::setEnvironmentVariable);
        os.set_function("getenv", System::getEnvironmentVariable);
        os.set_function("setcwd", System::setCurrentDirectory);
        os.set_function("getcwd", System::getCurrentDirectory);

        /// lua standard `loadstring`: 廃止
        lua["loadstring"] = sol::nil;

        /* // lua standard `load` が string + byte code に対応しているため不要
        /// lua standard `load`: string + byte code に対応
        lua["load"].set_function(sol::overload(
            [&lua](const std::string &script, const std::string &chunkname) { return loadstring(lua, script, chunkname); },
            [&lua](const std::string &script) { return loadstring(lua, script); },
            [&lua](Aula::IO::Binary *buffer, u32 buffersize, const std::string &chunkname) { return loadbuffer(lua, buffer, buffersize, chunkname); },
            [&lua](Aula::IO::Binary *buffer, u32 buffersize) { return loadbuffer(lua, buffer); },
            [&lua](Aula::IO::Binary *buffer, const std::string &chunkname) { return loadbuffer(lua, buffer, u32(-1), chunkname); },
            [&lua](Aula::IO::Binary *buffer) { return loadbuffer(lua, buffer); }
        ));
        */
    }
}