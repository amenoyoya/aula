%~d0
cd "%~dp0"

call ..\vcvars.bat

cd .\LuaJIT-2.1.0-beta3\src
call msvcbuild.bat static

del *.exp
move *.exe ..\..\..\dist\bin\x86\
move *.lib ..\..\..\dist\lib\x86\
