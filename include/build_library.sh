cd $(dirname $0)

export CPLUS_INCLUDE_PATH="$(pwd):$(pwd)/../extlib/LuaJIT-2.1.0-beta3/src:$(pwd)/../extlib/zlib-1.2.8:$(pwd)/../extlib/sol2-3.2.2"

# generate lua stdlib codes
/bin/bash ./aula/lua/_generate_stdlib_code.sh

# build aula library
g++ -c -O2 -std=c++17 -s -DNDEBUG ./aula/core/*.cpp
g++ -c -O2 -std=c++17 -s -DNDEBUG ./aula/zip/*.cpp
g++ -c -O2 -std=c++17 -s -DNDEBUG ./aula/lua/*.cpp

ar rcs libaula.a ./*.o
rm ./*.o
mv libaula.a ../dist/lib/x64/
