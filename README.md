# aula

A Lua script engine for a standalone utility application.

## Features

- Supports relative module searching system.
    - If you write `require` function with module name including `/`, the module will be searched from relative file path.
        - In this case, `.` is not replaced into `/`. So you want to require `./relative/module.lua`, you must write like below.
            - ✅ `require("./relative/module")`
            - ❌ `require("./relative.module")`
    - If module name has no `/`, the default require system will be executed.
        - e.g. `require("compat53.module")`
            - Search `compat53/module.lua`, `compat53/module/init.lua` ...etc
- Supports [Teal](https://github.com/teal-language/tl) - a typed dialect of Lua.
    - `teal.transpile(code: string, code_name: string): {luacode: string, err: string}`
        - Transpile Teal code to Lua code.
    - `teal.*`: See https://github.com/teal-language/tl/blob/master/docs/tutorial.md
- Supports [lua-compat-53](https://github.com/keplerproject/lua-compat-5.3)
    - `require("compat53")`
        - Load `compa53` module from the Aula engine resource (appended zip file). 
    - `require("compat53.module")`
        - Load `compa53.module` module from the Aula engine resource (appended zip file).

***

## Usage

```bash
# display help message
$ aula help

Aula is a Lua script engine.

Usage:
    aula [command] [script_file] [arguments]
    
The commands are:
    help        display information about Aula script engine
    version     display Aula version
    transpile   transpile Teal code to Lua code
            Usage:          $ aula transpile <input_teal_script_file> <output_lua_script_file>
            Description:    Aula will transpile <input_teal_script_file> to <output_lua_script_file>
    compile     compile Lua / Teal code to byte-code
            Usage:          $ aula compile <input_lua_script_file> <output_byte_code_file>
            Description:    Aula will compile <input_lua_script_file> to <output_byte_code_file>
    test        execute test codes
            Usage:          $ aula test [directory (default: ./)]
            Description:    Aula will execute test script files like "*_test.lua", "*_test.tl" in the <directory> and the sub directories

The script file will be executed:
    If the "main.lua" file exists at the directory containing Aula: execute a plain Lua script file
    Or if the "main.sym" file exists at the directory containing Aula: execute a compiled Lua byte-code file
    Or if the "main.tl" file exists at the directory containing Aula: execute a Teal script file
    Or if the command line arguments[1] is "*.lua" file: execute a plain Lua script file
    Or if the command line arguments[1] is "*.sym" file: execute a ompiled Lua byte-code file
    Or if the command line arguments[1] is "*.tl" file: execute a Teal script file
    
    
Aula will be executed as interactive-mode if there are no commands and script files.
```

***

## Environment

- OS:
    - Windows 10
    - Ubuntu 20.04
- Build tools:
    - Microsoft Visual C++ 2019 Build Tools
    - gcc: `9.3.0`
- Editor:
    - VSCode

***

## Development

Read [Development.md](./Development.md)

***

## TODO

- try [moonjit](https://github.com/moonjit/moonjit) instead of luajit
