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
> .\src\aula\build_library.bat
> .\src\aula\build_lua_library.bat
```

### Build Aula main engine & Test
```powershell
> .\src\build.bat

# => Aula engine: dist/bin/x86/aula.exe

# Unit test
> .\dist\x86\aula.exe .\test\apitest.lua
```

***

## TODO

- 64bit support
- Cross platform support
- try [moonjit](https://github.com/moonjit/moonjit) instead of luajit
- improve Aula.Encoding speed
    - => improved a little bit by using `std::move`
