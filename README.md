# aula

A Lua script engine for a standalone utility application

## Usage

```bash
# display help message
$ aula help

Usage:
    aula [command] [script_file] [arguments]

The commands are:
    help    display information about Aula script engine
    version display Aula version
    test    execute test codes
            Usage:  aula test [directory (default: ./)]
            Description:    Aula will execute test script files like "*_test.lua" in the target directory and the sub directories

The script file will be executed:
    If the command line arguments[1] is "*.lua" file (Plain lua source code file)
    Or if the command line arguments[1] is "*.sym" file (Compiled lua byte code file)
    Or if the "main.lua" file exists at the directory containing Aula
    Or if the "main.sym" file exists at the directory containing Aula

Aula will be executed as interactive-mode if there are no commands and script files.
```

***

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
> .\src\lib\build_library.bat
> .\src\lib\build_lua_library.bat
```

### Build Aula main engine & Test
```powershell
> .\src\build.bat

# => Aula engine compiled to: ./dist/bin/x86/aula.exe

# Unit test
> .\dist\bin\x86\aula.exe test

## or Specify unit test directory: .\test\
> .\dist\bin\x86\aula.exe test .\test

## => unit test files will be tested
###   - ./test/api_test.lua
###   - ./test/dotty_test.lua
###   - ./test/readln_test.lua
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
$ /bin/bash ./src/lib/build_library.sh
$ /bin/bash ./src/lib/build_lua_library.sh
```

### Build Aula main engine & Test
```bash
$ /bin/bash ./src/build.sh

# => Aula engine compiled to: ./dist/bin/x64/aula

# Unit test
$ ./dist/bin/x64/aula test

## or Specify unit test directory: ./test/
$ ./dist/bin/x64/aula test ./test

## => unit test files will be tested
###   - ./test/api_test.lua
###   - ./test/dotty_test.lua
###   - ./test/readln_test.lua
```

***

## TODO

- try [moonjit](https://github.com/moonjit/moonjit) instead of luajit
- improve Aula.Encoding speed
    - => improved a little bit by using `std::move`
