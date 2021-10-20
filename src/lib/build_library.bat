%~d0
cd %~dp0

call ..\..\vcvars.bat

:: build core library
cd %~dp0\core\encoding
%compile% *.cpp

cd ..\system
%compile% *.cpp

cd ..\path
%compile% *.cpp

cd ..\io
%compile% *.cpp

cd ..
lib.exe /OUT:"libaula_core.lib" /NOLOGO encoding\*.obj system\*.obj path\*.obj io\*.obj
del encoding\*.obj system\*.obj path\*.obj io\*.obj
move libaula_core.lib ..\..\..\dist\lib\x86\

:: build zip library
cd %~dp0
%compile% zip/*.cpp
lib.exe /OUT:"libaula_zip.lib" /NOLOGO *.obj
del *.obj
move libaula_zip.lib ..\..\dist\lib\x86\
