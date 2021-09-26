--[[
    ライブラリのロード順
    1. table
    2. string
    3. lpeg
    4. main (this file)
]]

-- System関連ライブラリ（osテーブルに統合）
os.execute = Aula.System.execute
os.sleep = Aula.System.sleep
os.systime = Aula.System.getTime
os.setenv = Aula.System.setEnvironmentVariable
os.getenv = Aula.System.getEnvironmentVariable
os.setcwd = Aula.System.setCurrentDirectory
os.getcwd = Aula.System.getCurrentDirectory


-- ffi関数
ffi = require "ffi"

if ffi.os == "Windows" then
    -- UTF-8 <-> wchar_t[]
    ffi.cdef[[
    bool utf8ToWideString(const char *src, wchar_t *dest, unsigned long size);
    bool wideStringToUTF8(const wchar_t *src, char *dest, unsigned long size);
    ]]
    
    Aula.Encoding.utf8ToWideString = function(src)
        local size = src:len()
        local dest = ffi.new("wchar_t["..(size+1).."]")
        ffi.C.utf8ToWideString(src, dest, size)
        return dest
    end
    
    Aula.Encoding.wideStringToUTF8 = function(src)
        local size = ffi.sizeof(src)
        local dest = ffi.new("char["..(size+1).."]")
        ffi.C.wideStringToUTF8(src, dest, size)
        return ffi.string(dest)
    end
end
