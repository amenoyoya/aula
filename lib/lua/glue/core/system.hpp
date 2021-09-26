#pragma once

#include "../../../core/system/base.hpp"

namespace Aula {
    inline void open_system_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto system = aula["System"].get_or_create<sol::table>();

        system.set_function("execute", System::execute);
        system.set_function("sleep", System::sleep);
        system.set_function("getTime", System::getTime);
        system.set_function("setEnvironmentVariable", System::setEnvironmentVariable);
        system.set_function("getEnvironmentVariable", System::getEnvironmentVariable);
        system.set_function("setCurrentDirectory", System::setCurrentDirectory);
        system.set_function("getCurrentDirectory", System::getCurrentDirectory);
    }
}