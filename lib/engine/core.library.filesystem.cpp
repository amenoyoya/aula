/*** Aulaエンジン用追加ライブラリ ***/
/* Aula.File.write */
// (string binary, u32 size, u32 n=1) -> u32
static int writeFile(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isusertype(L, 1, "Aula::File", 0, &tolua_err) || !tolua_isstring(L, 2, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::File::write'.", &tolua_err);
        return 0;
    }
    File *self = (File*)tolua_tousertype(L, 1, 0);
    if(!self){
        tolua_error(L, "invalid 'self' in function 'Aula::File::write'", nullptr);
        return 0;
    }
    size_t size;
    const char *bin = lua_tolstring(L, 2, &size);
    lua_pushnumber(L, self->write(bin, lua_type(L, 3) == LUA_TNUMBER? lua_tointeger(L, 3): size,
        lua_type(L, 4) == LUA_TNUMBER? lua_tointeger(L, 4): 1));
    return 1;
}

/* Aula.File.read, Aula.ZipFileReader.read, Aula.FileReader.read */
// (u32 size, u32 n=1) -> string binary
#define DEF_READ(File) \
static int read##File(lua_State *L){\
    tolua_Error tolua_err;\
    if(!tolua_isusertype(L, 1, "Aula::"#File, 0, &tolua_err) || !tolua_isnumber(L, 2, 0, &tolua_err)){\
        tolua_error(L, "#ferror in function 'Aula::"#File"::read'.", &tolua_err);\
        return 0;\
    }\
    File *self = (File *)tolua_tousertype(L, 1, 0);\
    if(!self){\
        tolua_error(L, "invalid 'self' in function 'Aula::"#File"::read'.", nullptr);\
        return 0;\
    }\
    u32 size = lua_tointeger(L, 2), n = lua_type(L, 3) == LUA_TNUMBER? lua_tointeger(L, 3): 1;\
    string buffer;\
    buffer.resize(size * n);\
    self->read((void*)&buffer[0], size, n);\
    lua_pushlstring(L, buffer.c_str(), size * n);\
    return 1;\
}

DEF_READ(File)
DEF_READ(ZipFileReader)
DEF_READ(FileReader)
#undef DEF_READ

/* Aula.ZipArchiver.append */
// (string filename, string binary, u32 size, string password="", u8 level=6, string comment="") -> boolean
static int appendZipArchiver(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isusertype(L, 1, "Aula::ZipArchiver", 0, &tolua_err)
        || !tolua_isstring(L, 2, 0, &tolua_err) || !tolua_isstring(L, 3, 0, &tolua_err))
    {
        tolua_error(L, "#ferror in function 'Aula::ZipArchiver::append'.", &tolua_err);
        return 0;
    }
    ZipArchiver *self = (ZipArchiver*)tolua_tousertype(L, 1, 0);
    if(!self){
        tolua_error(L, "invalid 'self' in function 'Aula::ZipArchiver::append'", nullptr);
        return 0;
    }
    size_t size;
    const char *bin = lua_tolstring(L, 3, &size);
    lua_pushboolean(L, self->append(lua_tostring(L, 2), bin, lua_type(L, 4) == LUA_TNUMBER? lua_tointeger(L, 4): size,
        lua_type(L, 5) == LUA_TSTRING? lua_tostring(L, 5): "", lua_type(L, 6) == LUA_TNUMBER? lua_tointeger(L, 6): 6,
        lua_type(L, 7) == LUA_TSTRING? lua_tostring(L, 7): ""));
    return 1;
}

/* Aula.ZipArchiver.readCurrentFile */
// (u32 size) -> string binary
static int readZipArchiverCurrentFile(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isusertype(L, 1, "Aula::ZipArchiver", 0, &tolua_err) || !tolua_isnumber(L, 2, 0, &tolua_err)) {
        tolua_error(L, "#ferror in function 'Aula::ZipArchiver::readCurrentFile'.", &tolua_err);
        return 0;
    }
    ZipArchiver *self = (ZipArchiver*)tolua_tousertype(L, 1, 0);
    if(!self){
        tolua_error(L, "invalid 'self' in function 'Aula::ZipArchiver::readCurrentFile'", nullptr);
        return 0;
    }
    u32 size = lua_tointeger(L, 2);
    string buf;
    buf.resize(size);
    self->readCurrentFile((void*)&buf[0], size);
    lua_pushlstring(L, buf.c_str(), size);
    return 1;
}


/* ファイルを列挙し，tableに格納 */
// (string dir, int nest=1, int opt=2) -> table
// * dir: ディレクトリ
// * nest: 列挙深度(0なら列挙しない，マイナスなら無制限)
// * opt: 列挙オプション(2=全て列挙，1=ファイルのみ列挙，0=ディレクトリのみ列挙)
static void enumfiles(lua_State *L, u32 &index, const string &dir, s32 nest, u8 opt){
    if(nest == 0) return;
    
    FileEnumerator f(dir);
    while(getState(&f) == Object::ACTIVE){
        const string &name = f.getName();
        if(name != "." && name != ".."){
            string path = f.getPath();
            
            if(Path::isDirectory(path)){
                if(opt != 1){
                    lua_pushstring(L, path.c_str());
                    lua_rawseti(L, -2, ++index);
                }
                enumfiles(L, index, path, nest-1, opt);
            }else{
                if(opt != 0){
                    lua_pushstring(L, path.c_str());
                    lua_rawseti(L, -2, ++index);
                }
            }
        }
        f.toNext();
    }
}

static int enumerateFiles(lua_State *L){
    tolua_Error tolua_err;
    if(!tolua_isstring(L, 1, 0, &tolua_err)){
        tolua_error(L, "#ferror in function 'Aula::enumerateFiles'.", &tolua_err);
        return 0;
    }
    
    u32 index = 0;
    lua_createtable(L, 0, 0);
    enumfiles(L, index, lua_tostring(L, 1), lua_type(L, 2) == LUA_TNUMBER? lua_tointeger(L, 2): 1,
        lua_type(L, 3) == LUA_TNUMBER? (s8)lua_tointeger(L, 3): 2);
    return 1;
}
