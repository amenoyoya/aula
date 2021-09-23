#include "main.h"
#include "luautf8/lutf8lib.c"
#include "lpeg-1.0.0/lpcap.c"
#include "lpeg-1.0.0/lpcode.c"
#include "lpeg-1.0.0/lpprint.c"
#include "lpeg-1.0.0/lptree.c"
#include "lpeg-1.0.0/lpvm.c"
#include "tolua/gluecode/core.cpp"

namespace Aula{
    namespace Engine{
        #include "core.library.cpp"
        #include "core.library.filesystem.cpp"
        
        /* SeleneTalk/Coreライブラリ */
        static u8 table_lib_code[] = {
            #include "corelib/Table.cpp"
        }, string_lib_code[] = {
            #include "corelib/String.cpp"
        }, lpeg_lib_code[] = {
            #include "corelib/LPeg.cpp"
        }, main_lib_code[] = {
            #include "corelib/Main.cpp"
        };
        
        
        /* LuaにCoreライブラリ登録 */
        bool registerCoreLibrary(lua_State *L){
            luaL_openlibs(L); // 標準ライブラリopen
            luaopen_utf8(L); // UTF-8サポート
            lua_setglobal(L, "utf8");
            luaopen_lpeg(L); // Parsing Expression Grammar for Lua
            // Aula基本ライブラリ登録
            tolua_libAula_core_open(L);
            // package.loaders設定
            lua_getglobal(L, "package");
            lua_getfield(L, -1, "loaders");
            lua_pushcfunction(L, script_loader);
            lua_rawseti(L, -2, 2); // package.loaders[2] = script_loader(相対パスrequire)
            lua_pop(L, 2);
            /* SeleneTalk追加ライブラリ登録 */
            lua_getglobal(L, "Aula");
            lua_pushcfunction(L, getCRC32);
            lua_setfield(L, -2, "getCRC32");
            lua_pushcfunction(L, base64encode);
            lua_setfield(L, -2, "base64encode");
            lua_pushcfunction(L, base64decode);
            lua_setfield(L, -2, "base64decode");
            lua_pushcfunction(L, enumerateFiles);
            lua_setfield(L, -2, "enumerateFiles");
            // Aula::LibraryLoader::getFunction
            lua_getfield(L, -1, "LibraryLoader");
            tolua_unlockclass(L); // -2:LibraryLoader<plain> | -1:meta
            lua_pushcfunction(L, getLibraryFunction);
            lua_setfield(L, -3, "getFunction");
            tolua_lockclass(L); // -1:Aula
            // Aula::File::write,read
            lua_getfield(L, -1, "File");
            tolua_unlockclass(L); // -2:File<plain> | -1:meta
            lua_pushcfunction(L, writeFile);
            lua_setfield(L, -3, "write");
            lua_pushcfunction(L, readFile);
            lua_setfield(L, -3, "read");
            tolua_lockclass(L); // -1:Aula
            // Aula::ZipFileReader::read
            lua_getfield(L, -1, "ZipFileReader");
            tolua_unlockclass(L); // -2:ZipFileReader<plain> | -1:meta
            lua_pushcfunction(L, readZipFileReader);
            lua_setfield(L, -3, "read");
            tolua_lockclass(L); // -1:Aula
            // Aula::FileReader::read
            lua_getfield(L, -1, "FileReader");
            tolua_unlockclass(L); // -2:FileReader<plain> | -1:meta
            lua_pushcfunction(L, readFileReader);
            lua_setfield(L, -3, "read");
            tolua_lockclass(L); // -1:Aula
            // Aula::ZipArchiver追加メソッド登録
            lua_getfield(L, -1, "ZipArchiver");
            tolua_unlockclass(L); // -2:ZipArchiver<plain> | -1:meta
            lua_pushcfunction(L, appendZipArchiver);
            lua_setfield(L, -3, "append");
            lua_pushcfunction(L, readZipArchiverCurrentFile);
            lua_setfield(L, -3, "readCurrentFile");
            tolua_lockclass(L); // -1:Aula
            // Aula::Engine::loadString, require
            lua_getfield(L, -1, "Engine");
            lua_pushcfunction(L, loadString);
            lua_setfield(L, -2, "loadString");
            lua_pushcfunction(L, require);
            lua_setfield(L, -2, "require");
            lua_pop(L, 2);
            // Aula/Coreライブラリ登録
            if(0 != luaL_loadbuffer(L, (const char*)table_lib_code, sizeof(table_lib_code), "<Aula/Define/Table>")
                || 0 != lua_pcall(L, 0, 0, 0)) return false;
            if(0 != luaL_loadbuffer(L, (const char*)string_lib_code, sizeof(string_lib_code), "<Aula/Define/String>")
                || 0 != lua_pcall(L, 0, 0, 0)) return false;
            if(0 != luaL_loadbuffer(L, (const char*)lpeg_lib_code, sizeof(lpeg_lib_code), "<Aula/Define/LPeg>")
                || 0 != lua_pcall(L, 0, 0, 0)) return false;
            if(0 != luaL_loadbuffer(L, (const char*)main_lib_code, sizeof(main_lib_code), "<Aula/Define/Main>")
                || 0 != lua_pcall(L, 0, 0, 0)) return false;
            return true;
        }
    }
}
