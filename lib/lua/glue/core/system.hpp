#pragma once

#include "../../../core/system/base.hpp"

namespace Aula {
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
    }
}