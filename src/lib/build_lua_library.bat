%~d0
cd %~dp0

call ..\..\vcvars.bat

:: build aula lua engine library
call %~dp0lua\_generate_stdlib_code.bat
cd %~dp0
%compile% lua\*.cpp
lib.exe /OUT:"libaula_lua.lib" /NOLOGO *.obj
del *.obj
move libaula_lua.lib ..\..\dist\lib\x86\
