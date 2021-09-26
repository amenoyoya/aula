#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "../core.hpp"

namespace Aula {
    namespace Lua {
        void registerCoreLibrary(sol::state &lua);
        void registerZipLibrary(sol::state &lua);
    }
}