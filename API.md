# Aula Library API

## C++ API

### types

- header: `lib/core/base/types.h`
- description:
    - 型定義

#### definition
- `i8`: 8bit signed integer
- `u8`: 8bit unsigned integer
- `i16`: 16bit signed integer
- `u16`: 16bit unsigned integer
- `i32`: 32bit signed integer
- `u32`: 32bit unsigned integer

### Core library
```bash
core/encoding/base
  |_ core/base/object
       |_ core/base/types

core/io/filesystem
  |_ core/io/fileenumerator
       |_ core/io/file
            |_ core/path/base
            |    |_ core/encoding/base
            |_ core/io/binary
                 |_ core/io/seekfrom
                      |_ core/encoding/base

core/system/base
  |_ core/path/base
       |_ core/encoding/base
```

### Lua exported API
reference: [src/aula/lua/glue](./src/aula/lua/glue)

***

## Lua API

- Extented functions: [src/aula/lua/stdlib](./src/aula/lua/stdlib)
- CommandLine arguments: `os.argv` {`std::vector<std::string>`}
     - `os.argv[1]`: Current process file path
          - e.g. `/path/to/dist/bin/aula`
     - `os.argv[2]`: Current executing script file path
          - e.g. `/path/to/main.lua`
     - `os.argv[3...]`: CommandLine arguments
