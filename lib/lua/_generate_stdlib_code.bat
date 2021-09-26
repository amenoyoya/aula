%~d0
cd %~dp0

@set PATH=%~dp0..\..\dist\bin\x86;%PATH%

cd stdlib
luajit _compile.lua
