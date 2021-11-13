%~d1
cd "%~dp1"

call "%~dp0vcvars.bat"

@set compile=cl.exe /c /nologo /std:c++17 /W3 /WX- /O2 /Oi /Oy- /D _CRT_SECURE_NO_WARNINGS /D WIN32 /D _MBCS /Gm- /EHsc /MTd /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Gd /analyze- /errorReport:none

%compile% "%~n1.cpp"
link.exe /ERRORREPORT:NONE /NOLOGO /MACHINE:X86 /OUT:"%~n1.exe" "%~n1.obj"
del "%~n1.obj"
del "%~n1.lib"
del "%~n1.exp"
