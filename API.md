# Aula Library API

## types

- header: `lib/core/base/types.h`
- description:
    - 型定義

### definition
- `i8`: 8bit signed integer
- `u8`: 8bit unsigned integer
- `i16`: 16bit signed integer
- `u16`: 16bit unsigned integer
- `i32`: 32bit signed integer
- `u32`: 32bit unsigned integer

***

## Source file dependencies

### Core library
```bash
core/encoding/base
  |_ core/string/base
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
  |_ core/encoding/base
```
