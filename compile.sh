export CPLUS_INCLUDE_PATH="$(pwd)/include:$(pwd)/extlib/LuaJIT-2.1.0-beta3/src:$(pwd)/extlib/zlib-1.2.8:$(pwd)/extlib/sol2-3.2.2"

g++ -O2 -std=c++17 -L"$(pwd)/dist/lib/x64" -static -static-libstdc++ -o ${1%.*} $1 -lluajit -ldl 
