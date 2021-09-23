call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

@set include=%~dp0extlib\LuaJIT-2.1.0-beta3\src;%~dp0extlib\tolua++-1.0.93\include;%~dp0extlib\zlib-1.2.8;%include%
@set lib=%~dp0extlib\LuaJIT-2.1.0-beta3\src;%~dp0extlib\tolua++-1.0.93\src\lib;%~dp0extlib\zlib-1.2.8;%lib%

@set compile=cl.exe /c /nologo /W3 /WX- /O2 /Oi /Oy- /D _CRT_SECURE_NO_WARNINGS /D WIN32 /D NDEBUG /D _MBCS /Gm- /EHsc /MT /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Gd /analyze- /errorReport:none
