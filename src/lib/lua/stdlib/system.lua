--- overload lua standard load function ---

-- @param {string} filename
--     - `*.lua`: load as a lua code
--     - `*.sym`: load as a compiled lua byte code (mode must be set)
--     - `*.tl`:  load as a teal code
-- @param {string} mode (default: "bt"): {"b": バイナリモード, "t": テキストモード, "bt": バイナリ＋テキストモード}
-- @param {table} env (default: _ENV)
-- @returns {function, string} loader, error_message
function loadfile(filename, mode, env)
    local code = Aula.IO.readFile(filename):toString()
    local ext = Aula.Path.getExtension(filename)

    -- transpile teal => lua if the file is `*.tl`
    if ext == ".tl" then
        local luacode, err = teal.transpile(code, filename)
        
        if luacode == nil then
            return nil, err
        end
        code = luacode
    end
    return load(code, "@" .. filename .. (ext == ".tl" and ".lua" or ""), mode, env)
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
        filename:same("@", true, 1) and filename:sub(2) or filename -- skip head `@`
    )
end



--- package.loaders 拡張 ---

-- 呼び出し元スクリプトからの相対パスで require スクリプト指定
function include(modname)
    local filename = debug.getinfo(2, "S").source
    local dirname = Aula.Path.getParentDirectory(
        filename:same("@", true, 1) and filename:sub(2) or filename -- skip head `@`
    )
    return require(Aula.Path.appendSlash(dirname) .. modname)
end

-- package path for searching
package.libpath = {"?", "?.lua", "?.sym", "?.tl", "?/main.lua", "?/main.sym", "?/main.tl", "?.dll", "?.so"}

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
            
            -- 拡張子が lua, sym, tl なら loadfile
            if ext == ".lua" or ext == ".sym" or ext == ".tl" then
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


-- UTF-8文字列出力関数
-- デフォルト print 関数を overload
function print(...)
    local list = {...}
    local n = #list
    if n == 0 then
        Aula.IO.Stdout:write "nil"
    else
        for i = 1, n do
            Aula.IO.Stdout:write(
                (i == 1 and "" or "\t") .. (type(list[i]) == 'table' and table.serialize(list[i], 2) or tostring(list[i])),
                false
            )
        end
        Aula.IO.Stdout:write "" -- \n
    end
end

-- フォーマット付きUTF-8文字列出力
function printf(format, ...)
    Aula.IO.Stdout:write(format:format(...), false)
end

-- フォーマット付きerror出力
function errorf(format, ...)
    return error(format:format(...))
end

-- コマンドラインから文字列を読み込む(UTF-8)
function readln(message, size)
    if type(message) == 'string' then
        Aula.IO.Stdout:write(message, false)
    end
    return Aula.IO.Stdin:readString(size or 1024)
end
