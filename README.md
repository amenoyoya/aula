# aula

A Lua script engine for a standalone utility application

## Environment

- OS:
    - Windows 10
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

# Build zlib
> .\extlib\build_zlib.bat
```

### Build Aula libraries
```powershell
> .\lib\build_library.bat
> .\lib\build_lua_library.bat
```

### Test
```powershell
> .\create_exe.bat .\test\aula_core.cpp
> .\test\aula_core.exe
```

### Build Aula main engine
```powershell
> .\src\build.bat

# => Aula engine: dist/bin/x86/aula.exe
```

***

## TODO

- 64bit support
- try [moonjit](https://github.com/moonjit/moonjit) instead of luajit
