%~d0
cd %~dp0

call ..\vcvars.bat

%compile% aula.cpp
@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:aula.exe aula.obj

del aula.exp aula.lib aula.obj
move aula.exe ..\dist\bin\x86\
