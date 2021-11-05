%~d0
cd %~dp0

call ..\..\vcvars.bat

%compile% sdl\*.cpp
lib.exe /OUT:"libaula_sdl.lib" /NOLOGO *.obj
del *.obj
move libaula_sdl.lib ..\..\dist\lib\x86\
