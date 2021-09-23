@call ..\..\vcvars.bat

::@%compile% minisltk.cpp
::@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 minisltk.obj libsltk3_engine.lib libsltk3_engine_win32.lib libsltk3_win32.lib libsltk3_zlib.lib libsltk3_core.lib tolua++.lib lua51.lib zlib.lib
::@move minisltk.exe ..\bin\win32\minisltk.exe
::@del minisltk.exp minisltk.lib minisltk.obj

@cd startuplib
@luajit .compile.sltk
@cd ..
@%compile% /D_WINDOWS /wd4309 SeleneTalk.cpp
@rc.exe /NOLOGO SeleneTalk.rc
@link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:SeleneTalk.exe SeleneTalk.obj SeleneTalk.res libsltk3_engine.lib libsltk3_engine_win32.lib libsltk3_win32.lib libsltk3_zlib.lib libsltk3_core.lib tolua++.lib lua51.lib zlib.lib
@move SeleneTalk.exe ..\bin\SeleneTalk.exe
@del SeleneTalk.obj SeleneTalk.res SeleneTalk.manifest SeleneTalk.lib SeleneTalk.exp
