#pragma once

#define UNICODE
#define SOL_ALL_SAFETIES_ON 1
#define SOL_LUAJIT 1
#include <sol/sol.hpp>
#include "../zip.hpp"

namespace aula {
    namespace lua {
        /// Register Libraries
        //  - Extended Lua standard libraries
        //  - Luz core library
        bool openlib(sol::state &lua, std::string *errorMessage);

        /// Execute interactive lua
        void dotty(sol::state &lua, const std::string &progname = "aula");
    }
}
