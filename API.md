# Aula Library API

## C++ API

### Core library
```bash
core/path
  |_ core/io
       |_ core/string
            |_ core/config

core/os
  |_ core/path

core/filesystem
  |_ core/path
```

### Lua exported API
reference: [include/aula/lua/glue](./include/aula/lua/glue)

***

## Lua API

- Extented functions: [include/aula/lua/stdlib](./include/aula/lua/stdlib)
- CommandLine arguments: `os.argv` {`std::vector<std::string>`}
     - `os.argv[0]`: Current process file path
          - e.g. `/path/to/dist/bin/aula`
     - `os.argv[1]`: Current executing script file path
          - e.g. `/path/to/main.lua`
     - `os.argv[2...]`: CommandLine arguments
