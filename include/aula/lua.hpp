#pragma once

#define SOL_ALL_SAFETIES_ON 1
#define SOL_LUAJIT 1
#include <sol/sol.hpp>
#include <aula/core.hpp>
#include <aula/zip.hpp>

// ライブラリリンク
#ifdef _MSC_VER
    #pragma comment(lib, "libaula_lua.lib")
    #pragma comment(lib, "lua51.lib")
#endif

namespace Aula {
    namespace Lua {
        /// Register Aula Library
        //  - Aula C++ core library
        //  - Aula C++ zip library
        //  - Lua standard library extended
        bool registerLibrary(sol::state &lua, std::string *errorMessage);

        /// Execute interactive lua
        void dotty(sol::state &lua, const std::string &progname = "aula");
    }
}
