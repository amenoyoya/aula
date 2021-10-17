# aula

A Lua script engine for a standalone utility application

## Environment

- OS:
    - Windows 10
    - Ubuntu 20.04
- Build tools:
    - Microsoft Visual C++ 2019 Community Edition
    - gcc: `9.3.0`
- Editor:
    - VSCode

***

## Development in Windows 10

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
> .\dist\bin\x86\aula.exe .\test\apitest.lua
```

***

## Development in Ubuntu 20.04

### Setup
```bash
# install gcc etc
$ sudo apt install -y build-essential

# install 32bit development libraries
# $ sudo apt install -y libc6-dev-i386
```

### Build external libraries
```bash
# Build LuaJIT
$ /bin/bash ./extlib/build_luajit.sh

# Build zlib
$ /bin/bash ./extlib/build_zlib.sh
```

### Build Aula libraries
```bash
$ /bin/bash ./src/aula/build_library.sh
$ /bin/bash ./src/aula/build_lua_library.sh
```

### Build Aula main engine & Test
```bash
$ /bin/bash ./src/build.sh

# => Aula engine: dist/bin/x64/aula

# Unit test
$ ./dist/bin/x64/aula ./test/apitest.lua
```

***

## TODO

- 64bit support
- Cross platform support
    - ❌ Currently, C++ exception is occurred at `Aula::IO::Stdin::readString` on Ubuntu 20.04
- try [moonjit](https://github.com/moonjit/moonjit) instead of luajit
- improve Aula.Encoding speed
    - => improved a little bit by using `std::move`
