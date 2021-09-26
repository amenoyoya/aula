#pragma once

#define SOL_ALL_SAFETIES_ON 1
#define SOL_LUAJIT 1
#include <sol/sol.hpp>
#include "../core.hpp"

namespace Aula {
    namespace Lua {
        /// Aula C++ core library 登録
        void registerCoreLibrary(sol::state &lua);

        /// Aula C++ zip library 登録
        void registerZipLibrary(sol::state &lua);

        /// Lua standard library 拡張スクリプト登録
        bool expandStandardLibrary(sol::state &lua, std::string *errorMessage);
    }
}