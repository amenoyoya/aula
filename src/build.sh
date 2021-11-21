cd "$(dirname $0)"

export CPLUS_INCLUDE_PATH="$(pwd)/../include:$(pwd)/../extlib/LuaJIT-2.1.0-beta3/src:$(pwd)/../extlib/zlib-1.2.8:$(pwd)/../extlib/sol2-3.2.2"

# build miniaula
g++ -O2 -s -DNDEBUG -std=c++17 -L"$(pwd)/../dist/lib/x64" -static -static-libstdc++ -o miniaula miniaula.cpp -laula -lzlib -lluajit -ldl

# build aula
g++ -O2 -s -DNDEBUG -std=c++17 -L"$(pwd)/../dist/lib/x64" -static -static-libstdc++ -o aula aula.cpp -laula -lzlib -lluajit -ldl

# bundle resource/main.lua into aula
./miniaula bundle.lua

mv miniaula ../dist/bin/x64/
mv aula ../dist/bin/x64/
