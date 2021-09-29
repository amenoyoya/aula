%~d0
cd "%~dp0"

call ..\vcvars.bat

%compile% interception.cpp
link.exe /ERRORREPORT:NONE /DLL /MACHINE:X86 /OUT:interception.dll interception.obj

move interception.dll ..\dist\bin\x86\
del interception.obj
del interception.exp
del interception.lib
