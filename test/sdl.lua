local ffi = require"ffi"

ffi.cdef[[
const char *SDL_GetError(void);
unsigned long SDL_RWFromFile(const char *, const char *);
size_t SDL_RWread(unsigned long, uint8_t *, size_t, size_t);
size_t SDL_RWclose(unsigned long);
]]

local buf = ffi.new("uint8_t[?]", 256)
local file = ffi.C.SDL_RWFromFile(package.__file, "r");

if file == 0 then
    error(ffi.C.SDL_GetError())
end

printf("size: %d\n", ffi.C.SDL_RWread(file, buf, 1, 256))
print(buf)
ffi.C.SDL_RWclose(file)
