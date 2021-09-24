/*** Aulaエンジン用追加ライブラリ ***/
/* LibraryLoader::getFunction */
// (string funcName) -> function
static int getLibraryFunction(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isusertype(L, 1, "Aula::LibraryLoader", 0, &tolua_err) || !tolua_isstring(L, 2, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::LibraryLoader::getFunction'.", &tolua_err);
        return 0;
    }
    LibraryLoader *self = (LibraryLoader*)tolua_tousertype(L, 1, 0);
    if(!self){
        tolua_error(L, "invalid 'self' in function 'Aula::LibraryLoader::getFunction'", nullptr);
        return 0;
    }
    int (*func)(lua_State*) = (int(*)(lua_State*))self->getFunction(lua_tostring(L, 2));
    if(!func) return 0;
    lua_pushcfunction(L, func);
    return 1;
}

/* Aula.getCRC32 */
// (string binary, u32 size, u32 head=0xffffff) -> u32
static int getCRC32(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isstring(L, 1, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::getCRC32'.", &tolua_err);
        return 0;
    }
    
    size_t size;
    const char *bin = lua_tolstring(L, 1, &size);
    lua_pushnumber(L, Aula::getCRC32(bin, lua_type(L, 2) == LUA_TNUMBER? lua_tointeger(L, 2): size,
        lua_type(L, 3) == LUA_TNUMBER? lua_tointeger(L, 3): 0xffffff));
    return 1;
}

/* Aula.base64encode */
// (string binary, u32 size) -> string binary
static int base64encode(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isstring(L, 1, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::base64encode'.", &tolua_err);
        return 0;
    }
    
    size_t size;
    const char *bin = lua_tolstring(L, 1, &size);
    lua_pushstring(L, Aula::base64encode(bin,
        lua_type(L, 2) == LUA_TNUMBER? lua_tointeger(L, 2): size).c_str());
    return 1;
}

/* Aula.base64decode */
// (string base64) -> string binary
static int base64decode(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isstring(L, 1, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::base64decode'.", &tolua_err);
        return 0;
    }
    
    string base64 = lua_tostring(L, 1), buffer;
    u32 size = Aula::base64decode(nullptr, base64);
    buffer.resize(size);
    Aula::base64decode((char*)&buffer[0], base64);
    lua_pushlstring(L, buffer.c_str(), size);
    return 1;
}


/* Aula.Engine.loadString */
// (string script, string chunkName="") -> [function [, string]]
static int loadString(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isstring(L, 1, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::Engine::loadString'.", &tolua_err);
        return 0;
    }
    
    size_t size;
    const char *script = lua_tolstring(L, 1, &size);
    if(0 != luaL_loadbuffer(L, script, size, lua_type(L, 2) == LUA_TSTRING? lua_tostring(L, 2): "string")){
        string err = lua_tostring(L, -1);
        lua_settop(L, 0);
        lua_pushnil(L);
        lua_pushstring(L, err.c_str());
        return 2;
    }
    return 1;
}


/* スクリプトファイルを探索してロード */
static int _require(lua_State *L, const string &modulename){
    FileReader *pReader = getFileReader(L);
    if(!pReader){
        lua_pushstring(L, "\n\tAula::Engine::reader not found.");
        return 1;
    }
    
    string ext = Path::getExtension(modulename), msg, err;
    u8 mode = isSameString(ext, ".lua")? 0: (isSameString(ext, ".sym")? 1: 2);
    
    if(mode < 2){ // スクリプトファイル
        pReader->open(modulename);
        switch(loadScriptFile(L, pReader, mode)){
        case -1:
            msg.append("\n\tfile '" + modulename + "' not found.");
            return 1;
        case 0:
            err = lua_tostring(L, -1);
            lua_settop(L, 0);
            return luaL_error(L, err.c_str());
        case 1:
            return 1;
        }
    }else{
        // スクリプト/プラグインファイルの拡張子でない場合、
        // ・modulename/__main.lua,  modulename.lua
        // ・modulename/__main.sym,  modulename.sym
        // を順に探す
        string files[] = {
            Path::appendSlash(modulename) + "__main.lua",  modulename + ".lua",
            Path::appendSlash(modulename) + "__main.sym",  modulename + ".sym",
        };
        u8 modes[] = {
            0, 0, 1, 1
        };
        for(u8 i = 0; i < 4; ++i){ // スクリプトファイル探索
            pReader->open(files[i]);
            switch(loadScriptFile(L, pReader, modes[i])){
            case -1:
                msg.append("\n\tfile '" + files[i] + "' not found.");
                break;
            case 0:
                err = lua_tostring(L, -1);
                lua_settop(L, 0);
                return luaL_error(L, err.c_str());
            case 1:
                return 1;
            }
        }
    }
    // スクリプト/プラグインファイルが見つからなかった
    lua_pushstring(L, msg.c_str());
    return 1;
}

/* Aula.Engine.require */
// (string modulename) -> function or string
static int require(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isstring(L, 1, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::Engine::require'.", &tolua_err);
        return 0;
    }
    return _require(L, lua_tostring(L, 1));
}

/* 相対パスからのスクリプトローダー */
// package.loaders[2]
static int script_loader(lua_State *L){
    string filename = lua_tostring(L, 1);
    lua_Debug debug;
    
    // 呼び出し元スクリプトのディレクトリからの相対パスに変換
    if(lua_getstack(L, 2, &debug)){
        lua_getinfo(L, "S", &debug);
        string dir = Path::getParentDirectory(debug.source, false);
        filename = (dir == ""? "": Path::appendSlash(dir)) + filename;
    }
    return _require(L, filename);
}
