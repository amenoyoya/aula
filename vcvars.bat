call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"

@set include=%~dp0include;%include%
@set include=%~dp0extlib\LuaJIT-2.1.0-beta3\src;%~dp0extlib\tolua++-1.0.93\include;%~dp0extlib\sol2-3.2.2;%~dp0extlib\zlib-1.2.8;%include%
@set include=%~dp0extlib\SDL2-2.0.16\include;%include%
@set lib=%~dp0dist\lib\x86;%lib%

@set compile=cl.exe /c /nologo /std:c++17 /W3 /WX- /O2 /Oi /Oy- /D _CRT_SECURE_NO_WARNINGS /D WIN32 /D NDEBUG /D _MBCS /Gm- /EHsc /MT /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Gd /analyze- /errorReport:none
