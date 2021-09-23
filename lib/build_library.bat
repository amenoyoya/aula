%~d0
cd %~dp0

call ..\vcvars.bat

:: build core library
%compile% core/*.cpp
lib.exe /OUT:"libaula_core.lib" /NOLOGO *.obj
del *.obj
move libaula_core.lib ..\dist\lib\x86\

:: build zlib library
%compile% zlib/*.cpp
lib.exe /OUT:"libaula_zlib.lib" /NOLOGO *.obj
del *.obj
move libaula_zlib.lib ..\dist\lib\x86\

:: build aula engine library
call engine/_generate_code.bat
cd %~dp0
%compile% engine/core.cpp engine/main.cpp
lib.exe /OUT:"libaula_engine.lib" /NOLOGO *.obj
del *.obj
move libaula_engine.lib ..\dist\lib\x86\
