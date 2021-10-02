%~d0
cd %~dp0

call ..\vcvars.bat

%compile% aula.cpp
rc.exe /NOLOGO aula.rc
@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:aula.exe aula.obj aula.res

move aula.exe ..\dist\bin\x86\
del aula.exp aula.lib aula.obj aula.res
