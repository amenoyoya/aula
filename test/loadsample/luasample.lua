print "Hello, Lua script"

-- debug.getinfo: [lua_getinfo](https://pgl.yoyo.org/luai/i/lua_getinfo)
-- @see [lua_Debug](https://pgl.yoyo.org/luai/i/lua_Debug)
print("This file is: " .. debug.getinfo(1, 'S').source)
