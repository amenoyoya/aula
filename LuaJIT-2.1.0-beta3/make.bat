%~d0
cd "%~dp0"

call ..\vcvars.bat

cd src
call msvcbuild.bat static
