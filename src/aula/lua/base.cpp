#include <aula/lua/base.hpp>

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
                sol::lib::coroutine,
                sol::lib::package,
                sol::lib::string,
                sol::lib::table,
                // sol::lib::io,
                sol::lib::math,
                sol::lib::os,
                sol::lib::debug,
                sol::lib::ffi,
                sol::lib::bit32,
                sol::lib::jit
            );

            luaopen_utf8(lua); // UTF-8 support
            lua_setglobal(lua, "utf8");

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

        /* Lua 標準ライブラリ拡張 */
        static u8 string_lib_code[] = {
            #include "stdlib/string.cpp"
        }, table_lib_code[] = {
            #include "stdlib/table.cpp"
        }, lpeg_lib_code[] = {
            #include "stdlib/lpeg.cpp"
        };

        static bool doLuaBuffer(sol::state &lua, const char *buffer, u32 bufferSize, const std::string &scriptName, std::string *errorMessage) {
            auto script = lua.load_buffer(buffer, bufferSize, scriptName.c_str());
            if (!script.valid()) {
                sol::error err = script;
                *errorMessage = Encoding::toUTF8(err.what());
                return false;
            }

            auto result = script();
            if (!result.valid()) {
                sol::error err = result;
                *errorMessage = Encoding::toUTF8(err.what());
                return false;
            }
            return true;
        }

        bool expandStandardLibrary(sol::state &lua, std::string *errorMessage) {
            if (!doLuaBuffer((const char*)string_lib_code, sizeof(string_lib_code), "<stdlib/string>", errorMessage)) return false;
            if (!doLuaBuffer((const char*)table_lib_code, sizeof(table_lib_code), "<stdlib/table>", errorMessage)) return false;
            if (!doLuaBuffer((const char*)lpeg_lib_code, sizeof(lpeg_lib_code), "<stdlib/lpeg>", errorMessage)) return false;
            return true;
        }
    }
}