%~d0
cd %~dp0

call ..\vcvars.bat

:: build miniaula
cd %~dp0
%compile% miniaula.cpp
@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:miniaula.exe miniaula.obj

:: build aula
%compile% aula.cpp
rc.exe /NOLOGO resource\aula.rc
@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:aula.exe aula.obj resource\aula.res

:: bundle resource/main.lua into aula
miniaula.exe bundle.lua

move miniaula.exe ..\dist\bin\x86\
move aula.exe ..\dist\bin\x86\
del *.exp *.lib *.obj resource\aula.res
