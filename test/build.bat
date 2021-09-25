%~d0
cd %~dp0

call ..\vcvars.bat
%compile% aula_core.cpp
link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:aula_core.exe aula_core.obj

del *.obj
del *.exp
del *.lib
