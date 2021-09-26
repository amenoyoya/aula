#pragma once

#include "../../../core/string/base.hpp"

namespace Aula {
    inline void open_string_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto str = aula["String"].get_or_create<sol::table>();

        str.set_function("isEqualFold", sol::overload(
            [](const std::string &s1, const std::string &s2, u32 len) { return String::isEqualFold(s1, s2, len); },
            [](const std::string &s1, const std::string &s2) { return String::isEqualFold(s1, s2); }
        ));
        str.set_function("replace", String::replace);
    }
}