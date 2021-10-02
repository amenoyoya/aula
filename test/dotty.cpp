﻿#include <aula/lua.hpp>

#define LUA_PROMPT	"> "	/* Interactive prompt. */
#define LUA_PROMPT2	">> "	/* Continuation prompt. */
#define LUA_MAXINPUT	512	/* Max. input line length. */

static void l_message(const std::string &pname, const std::string &msg) {
    if (pname.size() > 0) {
        Aula::IO::Stderr->write(pname + ": ", false);
    }
    Aula::IO::Stderr->write(msg);
    Aula::IO::Stderr->flush();
}

static int report(lua_State *L, int status, const char *progname) {
    if (status && !lua_isnil(L, -1)) {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        l_message(progname, msg);
        lua_pop(L, 1);
    }
    return status;
}

static int traceback(lua_State *L) {
    if (!lua_isstring(L, 1)) { /* Non-string error object? Try metamethod. */
        if (lua_isnoneornil(L, 1) || !luaL_callmeta(L, 1, "__tostring") || !lua_isstring(L, -1))
            return 1;  /* Return non-string error object. */
        lua_remove(L, 1);  /* Replace object by result of __tostring metamethod. */
    }
    luaL_traceback(L, L, lua_tostring(L, 1), 1);
    return 1;
}

static void write_prompt(lua_State *L, int firstline) {
    const char *p;
    lua_getfield(L, LUA_GLOBALSINDEX, firstline ? "_PROMPT" : "_PROMPT2");
    p = lua_tostring(L, -1);
    if (p == NULL) p = firstline ? LUA_PROMPT : LUA_PROMPT2;
    Aula::IO::Stdout->write(p, false);
    Aula::IO::Stdout->flush();
    lua_pop(L, 1);  /* remove global */
}

static int incomplete(lua_State *L, int status) {
    if (status == LUA_ERRSYNTAX) {
        size_t lmsg;
        const char *msg = lua_tolstring(L, -1, &lmsg);
        const char *tp = msg + lmsg - (sizeof(LUA_QL("<eof>")) - 1);
        if (strstr(msg, LUA_QL("<eof>")) == tp) {
            lua_pop(L, 1);
            return 1;
        }
    }
    return 0;  /* else... */
}

static int pushline(lua_State *L, int firstline) {
    write_prompt(L, firstline);

    std::string buf = Aula::IO::Stdin->readString(LUA_MAXINPUT);
    size_t len = buf.size();
    if (len > 0) {
        if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
        if (firstline && buf[0] == '=') lua_pushfstring(L, "return %s", buf.c_str() + 1);
        else lua_pushstring(L, buf.c_str());
        return 1;
    }
    return 0;
}

static int loadline(lua_State *L) {
    int status;
    lua_settop(L, 0);
    if (!pushline(L, 1)) return -1;  /* no input */
    for (;;) {  /* repeat until gets a complete line */
        status = luaL_loadbuffer(L, lua_tostring(L, 1), lua_strlen(L, 1), "=stdin");
        if (!incomplete(L, status)) break;  /* cannot try to add lines? */
        if (!pushline(L, 0))  /* no more input? */
        return -1;
        lua_pushliteral(L, "\n");  /* add a new line... */
        lua_insert(L, -2);  /* ...between the two lines */
        lua_concat(L, 3);  /* join them */
    }
    lua_remove(L, 1);  /* remove line */
    return status;
}

static int docall(lua_State *L, int narg, int clear) {
    int status;
    int base = lua_gettop(L) - narg;  /* function index */
    lua_pushcfunction(L, traceback);  /* push traceback function */
    lua_insert(L, base);  /* put it under chunk and args */
    status = lua_pcall(L, narg, (clear ? 0 : LUA_MULTRET), base);
    lua_remove(L, base);  /* remove traceback function */
    /* force a complete garbage collection in case of errors */
    if (status != LUA_OK) lua_gc(L, LUA_GCCOLLECT, 0);
    return status;
}

static void dotty(lua_State *L, const char *progname) {
    int status;
    while ((status = loadline(L)) != -1) {
        if (status == LUA_OK) status = docall(L, 0, 0);
        report(L, status, progname);
        if (status == LUA_OK && lua_gettop(L) > 0) {  /* any result to print? */
            lua_getglobal(L, "print");
            lua_insert(L, 1);
            if (lua_pcall(L, lua_gettop(L)-1, 0, 0) != 0)
                l_message(progname,
                    lua_pushfstring(
                        L, "error calling " LUA_QL("print") " (%s)",
                        lua_tostring(L, -1)
                    )
                );
        }
    }
    lua_settop(L, 0);  /* clear stack */
    Aula::IO::Stdout->write(""); // \n
    Aula::IO::Stdout->flush();
}


__main() {
    sol::state lua;
    std::string errorMessage;
    
    if (!Aula::Lua::registerLibrary(lua, &errorMessage)) {
        Aula::IO::Stderr->write(errorMessage);
        return 1;
    }
    dotty(lua, "dotty");
    return 0;
}