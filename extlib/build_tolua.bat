%~d0
cd %~dp0

call ..\vcvars.bat

cd .\tolua++-1.0.93\src\lib
%compile% *.c
lib.exe /OUT:"tolua++.lib" /NOLOGO *.obj
del *.obj
move tolua++.lib ..\..\..\..\dist\lib\x86\

cd ..\bin
%compile% tolua.c toluabind.c lua-5.1/*.c
link.exe /OUT:"tolua++.exe" /NOLOGO *.obj tolua++.lib
del *.obj
move tolua++.exe ..\..\..\..\dist\bin\x86\
