cd $(dirname $0)

export CPLUS_INCLUDE_PATH="$(pwd)/../../include:$(pwd)/../../extlib/LuaJIT-2.1.0-beta3/src:$(pwd)/../../extlib/zlib-1.2.8:$(pwd)/../../extlib/sol2-3.2.2"

# build core library
cd ./core/encoding
g++ -c -O2 *.cpp

cd ../system
g++ -c -O2 *.cpp

cd ../path
g++ -c -O2 *.cpp

cd ../io
g++ -c -O2 *.cpp

cd ..
ar rcs libaula_core.a ./encoding/*.o ./system/*.o ./path/*.o ./io/*.o
rm ./encoding/*.o ./system/*.o ./path/*.o ./io/*.o
mv libaula_core.a ../../../dist/lib/x64/

# build zip library
cd ../zip
g++ -c -O2 *.cpp
ar rcs libaula_zip.a *.o
rm *.o
mv libaula_zip.a ../../../dist/lib/x64/
