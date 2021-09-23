%~d0
cd %~dp0

@set PATH=%~dp0..\..\dist\bin\x86;%PATH%

cd corelib
luajit _compile.lua

cd ..\tolua
tolua++ -n libAula_core -o gluecode/core.cpp -H gluecode/core.h core.pkg
