--- Aula.IO.File easy read/write ---

-- @param {string} filename: Target file path
-- @param {number} size (default: file.size): Size for reading (byte)
-- @returns {Aula.IO.Binary} Read data
function Aula.IO.readFile(filename, size)
    local file = Aula.IO.File.new(filename, "rb")
    return file:getState() == Aula.Object.State.FAILED and Aula.IO.Binary.new() or file:read(size or file:getSize())
end

-- @param {string} filename: Target file path
-- @param {Aula.IO.Binary} data: Content data for writing
-- @param {number} size (default: data.size): Size for writing (byte)
-- @returns {number} Written size (byte)
function Aula.IO.writeFile(filename, data, size)
    local file = Aula.IO.File.new(filename, "wb")
    return file:getState() == Aula.Object.State.FAILED and 0 or file:write(data, size or data:getSize())
end


--- overload lua standard load function ---

-- @param {string} filename
-- @param {string} mode (default: "bt"): {"b": バイナリモード, "t": テキストモード, "bt": バイナリ＋テキストモード}
-- @param {table} env (default: _ENV)
-- @returns ({function} func, {string} errorMessage)
function loadfile(filename, mode, env)
    return load(Aula.IO.readFile(filename):toString(), filename, mode, env)
end

-- @param {string} filename
function dofile(filename)
    local f, err = loadfile(filename)
    if not f then
        error(err)
    end
    return f()
end


--- script file meta function ---

-- __file(): この関数の呼び出し元スクリプトファイル名を取得
function __file()
    local filename = debug.getinfo(2, "S").source
    -- skip head `@`
    return filename:same("@", true, 1) and filename:sub(2) or filename
end

-- __dir(): この関数の呼び出し元スクリプトファイルの親ディレクトリを取得
function __dir()
    local filename = debug.getinfo(2, "S").source
    return Aula.Path.getParentDirectory(
        filename:same("@", true, 1) and filename:sub(2) or filename, -- skip head `@`
        false -- not required real path (full path)
    )
end



--- package.loaders 拡張 ---

-- 呼び出し元スクリプトからの相対パスで require スクリプト指定
function include(modname)
    local filename = debug.getinfo(2, "S").source
    local dirname = Aula.Path.getParentDirectory(
        filename:same("@", true, 1) and filename:sub(2) or filename, -- skip head `@`
        false -- not required real path (full path)
    )
    return require(Aula.Path.appendSlash(dirname) .. modname)
end

-- package path for searching
package.libpath = {"?", "?.lua", "?.sym", "?/main.lua", "?/main.sym", "?.dll", "?.so"}

-- appendix loader for searching package.libpath
package.loaders[3] = function (filename)
    local errorMessage = ""

    for _, path in ipairs(package.libpath) do
        local filepath = Aula.Path.complete(path:replace("?", filename))

        if Aula.Path.isFile(filepath) then
            local ext = Aula.Path.getExtension(filepath)

            -- 拡張子が dll, so ならプラグインとして load
            -- エントリーポイント: 以下の内、先に見つかった関数を load する
            --  * luaopen_{module_name}
            --  * luaopen_module
            if ext == ".dll" or ext == ".so" then
                local loader = package.loadlib(filepath, "luaopen_" .. Aula.Path.getBaseStem(filename))
                if not loader then
                    loader = package.loadlib(filepath, "luaopen_module")
                end
                if not loader then
                    error("entry point function not found in module file '" .. filepath .. "'.")
                end
                return loader
            end
            
            -- 拡張子が lua, sym なら loadfile
            if ext == ".lua" or ext == ".sym" then
                local loader, err = loadfile(filepath)
                if not loader then
                    error(err)
                end
                return loader
            end
        end
        -- Update error message
        errorMessage = errorMessage .. "\n\tmodule '" .. filename .. "' not found in '" .. filepath .. "'."
    end
    return errorMessage
end
