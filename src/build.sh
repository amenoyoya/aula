cd "$(dirname $0)"

export CPLUS_INCLUDE_PATH="$(pwd)/../include:$(pwd)/../extlib/LuaJIT-2.1.0-beta3/src:$(pwd)/../extlib/zlib-1.2.8:$(pwd)/../extlib/sol2-3.2.2"

g++ -O2 -s -DNDEBUG -std=c++17 -L"$(pwd)/../dist/lib/x64" -static -static-libstdc++ aula.cpp -laula_lua -laula_zip -laula_core -lzlib -lluajit -ldl 
mv a.out ../dist/bin/x64/aula
