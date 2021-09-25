#include "base.h"
#include "glue/base.h"
#include "glue/string.h"
#include "glue/encoding.h"
#include "glue/path.h"
#include "glue/io.h"
#include "glue/system.h"

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

            registerBaseLibrary(lua);
            registerStringLibrary(lua);
            registerEncodingLibrary(lua);
            registerPathLibrary(lua);
            registerIoLibrary(lua);
            registerSystemLibrary(lua);
        }
    }
}