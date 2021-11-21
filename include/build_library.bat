%~d0
cd %~dp0

call ..\vcvars.bat

:: generate lua stdlib codes
call aula\lua\_generate_stdlib_code.bat

:: build aula library
cd %~dp0
%compile% aula\core\*.cpp
%compile% aula\zip\*.cpp
%compile% aula\lua\*.cpp

lib.exe /OUT:"libaula.lib" /NOLOGO *.obj
move libaula.lib ..\dist\lib\x86\
del *.obj
