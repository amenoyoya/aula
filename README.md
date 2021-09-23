# aula

A Lua script engine for a standalone utility application

## Environment

- OS:
    - Windows 10 64bit
- Build tools:
    - Microsoft Visual C++ 2019 Community Edition
- Editor:
    - VSCode

***

## Development

Make sure `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat` has been installed by Microsoft Visual C++ 2019 Community Edition.

Or you must edit `./vcvars.bat` file following to your Visual C++ environment.

### Build external libraries
```powershell
# Build LuaJIT
> .\extlib\build_luajit.bat

# Build tolua++
> .\extlib\build_tolua.bat

# Build zlib
> .\extlib\build_zlib.bat
```

### Build Aula libraries
```powershell
> .\lib\build_library.bat
```
