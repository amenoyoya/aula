%~d0
cd %~dp0

call ..\vcvars.bat

%compile% aula.cpp
@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:aula.exe aula.obj libaula_engine.lib libaula_zlib.lib libaula_core.lib tolua++.lib lua51.lib zlib.lib

del aula.exp aula.lib aula.obj
move aula.exe ..\dist\bin\x86\
