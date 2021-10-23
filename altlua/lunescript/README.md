# LuneScript for Aula

- original: https://github.com/ifritJP/LuneScript

## Changes

- Replace: `io.stdout` => `Aula.IO.Stdout`
- Replace: `io.stderr` => `Aula.IO.Stderr`
- `lune/base/Depend.lua`
    - in function: `getFileLastModifiedTime`
        - use `Aula.Path.getFileStatus`
- `lnsc.lua`
    - global variable: `arg`
        - use `os.argv`

## Usage

```bash
# Windows
$ ../../dist/bin/x86/aula lnsc.lua test.lns exe

# Ubuntu
$ ../../dist/bin/x64/aula lnsc.lua test.lns exe
```
