%~d0
cd %~dp0

call ..\vcvars.bat

:: build core library
cd %~dp0\core\string
%compile% *.cpp

cd ..\encoding
%compile% *.cpp

cd ..\system
%compile% *.cpp

cd ..\path
%compile% *.cpp

cd ..\io
%compile% *.cpp

cd ..
lib.exe /OUT:"libaula_core.lib" /NOLOGO string\*.obj encoding\*.obj system\*.obj path\*.obj io\*.obj
del string\*.obj encoding\*.obj system\*.obj path\*.obj io\*.obj
move libaula_core.lib ..\..\dist\lib\x86\

:: build zlib library
:: %compile% zlib/*.cpp
:: lib.exe /OUT:"libaula_zlib.lib" /NOLOGO *.obj
:: del *.obj
:: move libaula_zlib.lib ..\dist\lib\x86\

:: build aula lua engine library
cd %~dp0
%compile% lua/*.cpp
lib.exe /OUT:"libaula_lua.lib" /NOLOGO *.obj
del *.obj
move libaula_lua.lib ..\dist\lib\x86\
