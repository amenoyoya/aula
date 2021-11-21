# Development

## Development in Windows 10

### Setup
```powershell
# install visual c++ 2019 build tools by chocolatey
> choco install -y visualstudio2019buildtools --package-parameters "--add Microsoft.VisualStudio.Workload.VCTools --includeRecommended --includeOptional --passive
```

Make sure `C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars32.bat` has been installed by Chocolatey.

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
> .\include\build_library.bat
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


# Teal compiler error test
$ .\dist\bin\x86\aula .\altlua\teal\main.tl

========================================
3 errors:
.\altlua\teal\main.tl:5:10: cannot add undeclared function 'hello' outside of the scope where 'Character' was originally declared
.\altlua\teal\main.tl:16:4: invalid key 'hello' in record 'ch' of type Character
.\altlua\teal\main.tl:17:8: argument 1: got {integer} (inferred at .\altlua\teal\main.tl:17:9), expected Move
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
$ /bin/bash ./include/build_library.sh
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


# Teal compiler error test
$ ./dist/bin/x64/aula ./altlua/teal/main.tl

========================================
3 errors:
./altlua/teal/main.tl:5:10: cannot add undeclared function 'hello' outside of the scope where 'Character' was originally declared
./altlua/teal/main.tl:16:4: invalid key 'hello' in record 'ch' of type Character
./altlua/teal/main.tl:17:8: argument 1: got {integer} (inferred at ./altlua/teal/main.tl:17:9), expected Move
```
