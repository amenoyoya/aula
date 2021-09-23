--[[
    ライブラリのロード順
    -- Coreライブラリ
    1. Table
    2. String
    3. Main (this file)
]]

local bit = require "bit"

-- bit not
bnot = bit.bnot

-- N % n (1～n) 剰余計算
mod = function (N, n)
    local a = N % n
    return a == 0 and n or a
end

-- SeleneTalk Engine Script File Reader
Aula.Engine.reader = Aula.FileReader()

-- loadstring
loadstring = Aula.Engine.loadString


-- Aula.writeFile, Aula.readFile
Aula.writeFile = function(filename, data, size, n)
    local file, res = Aula.File(filename, "wb")
    if Aula.getState(file) == Aula.Object.FAILED then
        return 0
    end
    res = file:write(data, size, n)
    file:close()
    return res
end

Aula.readFile = function(filename, size, n)
    if not (Aula.Engine.reader:open(filename)) then
        return ""
    end
    local res = Aula.Engine.reader:read(size or Aula.Engine.reader:getSize(), n)
    Aula.Engine.reader:close()
    return res
end


-- Aula.ZipArchiver追加メソッド
local meta = getmetatable(Aula.ZipArchiver)
setmetatable(Aula.ZipArchiver, {})

Aula.ZipArchiver.openReadCurrentFile = function(self, size, password)
    local data = self:openCurrentFile(password) and self:readCurrentFile(size)
    self:closeCurrentFile()
    return data
end

setmetatable(Aula.ZipArchiver, meta)


-- System関連ライブラリ（osテーブルに統合）
os.execute = Aula.System.execute
os.sleep = Aula.System.sleep
os.systime = Aula.System.getTime
os.setenv = Aula.System.setEnvironmentVariable
os.getenv = Aula.System.getEnvironmentVariable
os.setcwd = Aula.System.setCurrentDirectory
os.getcwd = Aula.System.getCurrentDirectory


-- package.loaders追加
package.libloaders = {} -- LibraryLoaders配列
package.loadpath = {"", "."} -- 探索パス（空文字""は，requireにフルパスを渡したとき用）
-- package.loadpathテーブルからスクリプト/プラグイン探索
package.loaders[3] = function(filename)
    local msg, lib = "", Aula.LibraryLoader()
    
    for i = 1, #package.loadpath do
        local path = package.loadpath[i]
        local filepath = path == "" and filename or Aula.Path.appendSlash(path)..filename
        local ext = Aula.Path.getExtension(filename)
        
        -- 拡張子が dll, so ならプラグインとしてload
        if (ext:same".dll" or ext:same".so") and lib:open(filepath) then
            local loader = lib:getFunction"luaopen_module"
            if not (loader) then
                error("function 'luaopen_module' not found in module file '"..filepath.."'.")
            end
            package.libloaders[#package.libloaders + 1] = lib
            return loader
        end
        
        -- スクリプトファイルload
        local func = Aula.Engine.require(filepath)
        if type(func) == 'function' then
            return func
        end
        
        -- 拡張子を dll, so としてプラグインload
        local plugin = filepath..".dll"
        if lib:open(plugin) then
            local loader = lib:getFunction"luaopen_module"
            if not (loader) then
                error("function 'luaopen_module' not found in module file '"..plugin.."'.")
            end
            package.libloaders[#package.libloaders + 1] = lib
            return loader
        end
        plugin = filepath..".so"
        if lib:open(plugin) then
            local loader = lib:getFunction"luaopen_module"
            if not (loader) then
                error("function 'luaopen_module' not found in module file '"..plugin.."'.")
            end
            package.libloaders[#package.libloaders + 1] = lib
            return loader
        end
        -- エラーメッセージ更新
        msg = msg.."\n\tmodule '"..filename.."' not found in package.loadpath."
    end
    return msg
end


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
