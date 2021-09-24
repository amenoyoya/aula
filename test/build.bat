%~d0
cd %~dp0

call ..\vcvars.bat
%compile% sol_core.cpp
link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:sol_core.exe sol_core.obj libaula_core.lib lua51.lib

del *.obj
del *.exp
del *.lib
