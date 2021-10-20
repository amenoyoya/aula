cd $(dirname $0)

export CPLUS_INCLUDE_PATH="$(pwd)/../../include:$(pwd)/../../extlib/LuaJIT-2.1.0-beta3/src:$(pwd)/../../extlib/zlib-1.2.8:$(pwd)/../../extlib/sol2-3.2.2"

/bin/bash ./lua/_generate_stdlib_code.sh
g++ -c -O2 -s -DNDEBUG -std=c++17 ./lua/*.cpp

ar rcs libaula_lua.a ./*.o
rm ./*.o
mv libaula_lua.a ../../dist/lib/x64/
