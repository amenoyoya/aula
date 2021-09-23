%~d0
cd %~dp0

@set PATH=%~dp0..\..\extlib\LuaJIT-2.1.0-beta3\src;%~dp0..\..\extlib\tolua++-1.0.93\src\bin;%PATH%

cd corelib
luajit _compile.lua

cd ..\tolua
tolua++ -n libAula_core -o gluecode/core.cpp -H gluecode/core.h core.pkg
