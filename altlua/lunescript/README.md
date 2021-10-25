# LuneScript for Aula

- original: https://github.com/ifritJP/LuneScript

## Changes

- Replace: `io.stdout` => `Aula.IO.Stdout`
- Replace: `io.stderr` => `Aula.IO.Stderr`
- `lune/base/Depend.lua`
    - in function: `getFileLastModifiedTime`
        - use `Aula.Path.getFileStatus`
- `lune/base/TransUnit.lua`
    - import module エラー時に table print して stack overflow を起こすため、その部分を削除
        - comment out: `print( work, self.moduleScope )`
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
