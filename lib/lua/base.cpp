#include "base.h"
#include "glue/core/base.hpp"
#include "glue/core/string.hpp"
#include "glue/core/encoding.hpp"
#include "glue/core/path.hpp"
#include "glue/core/io.hpp"
#include "glue/core/system.hpp"
#include "glue/zip.hpp"

#include "luautf8/lutf8lib.c"
#include "lpeg-1.0.0/lpcap.c"
#include "lpeg-1.0.0/lpcode.c"
#include "lpeg-1.0.0/lpprint.c"
#include "lpeg-1.0.0/lptree.c"
#include "lpeg-1.0.0/lpvm.c"

namespace Aula {
    namespace Lua {
        void registerCoreLibrary(sol::state &lua) {
            // lua standard libraries
            lua.open_libraries(
                sol::lib::base,
                sol::lib::string,
                sol::lib::table,
                sol::lib::io,
                // sol::lib::file,
                sol::lib::math,
                // sol::lib::os,
                sol::lib::debug
            );

            luaopen_utf8(lua); // UTF-8 support
            // lua_setglobal(L, "utf8");
            luaopen_lpeg(lua); // Parsing Expression Grammar for Lua

            open_base_library(lua);
            open_string_library(lua);
            open_encoding_library(lua);
            open_path_library(lua);
            open_io_library(lua);
            open_system_library(lua);
        }

        void registerZipLibrary(sol::state &lua) {
            open_zip_library(lua);
        }
    }
}