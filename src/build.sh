export CPLUS_INCLUDE_PATH=../extlib/LuaJIT-2.0.4-sltk/src
export LIBRARY_PATH=../lib/linux

g++ -o minisltk -O2 -Wall -std=c++11 minisltk.cpp -lsltk3_engine -lsltk3_zlib -lsltk3_core -lluajit -ldl
mv minisltk ../bin/linux/minisltk
