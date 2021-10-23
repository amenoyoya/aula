--- extended Teal ---

-- teal configuration
-- * change this table if you want to change teal behavior
teal.config = {
    strict_mode = true,
    gen_compat = "required", -- "off" | "optional" | "required"
    gen_target = "5.1", -- "5.1" | "5.3"
    init_env_modules = {}, -- initial loaded modules
    _disabled_warnings_set = {},
    _warning_errors_set = {},
    
    -- error message writer
    error_writer = function (err)
        Aula.IO.Stderr:write(err)
    end,
}

-- override teal.process_string
-- * support for UTF-8 with BOM string
function teal.process_string(input, is_lua, env, filename)
    env = env or teal.init_env(is_lua)
    if env.loaded and env.loaded[filename] then
       return env.loaded[filename]
    end
    filename = filename or ""
 
    local syntax_errors = {}
    local tokens, errs = teal.lex(
        input:sub(1, 3) == "\xEF\xBB\xBF" and input:sub(4) or input
    )
    if errs then
       for _, err in ipairs(errs) do
          table.insert(syntax_errors, {
            y = err.y,
            x = err.x,
            msg = "invalid token '" .. err.tk .. "'",
            filename = filename,
          })
       end
    end
 
    local _, program = teal.parse_program(tokens, syntax_errors, filename)
 
    if (not env.keep_going) and #syntax_errors > 0 then
       local result = {
          ok = false,
          filename = filename,
          type_errors = {},
          syntax_errors = syntax_errors,
          env = env,
       }
       env.loaded[filename] = result
       table.insert(env.loaded_order, filename)
       return result
    end
 
    local opts = {
       filename = filename,
       lax = is_lua,
       gen_compat = env.gen_compat,
       env = env,
    }
    return teal.type_check(program, opts)
end

-- override teal.search_module
-- * support for simple package searching system
-- @returns {string, userdata, table} module_name, file_handler( has :close() method ), errors
function teal.search_module(module_name, search_dtl)
    local tried = {}

    -- search from relative path
    local filename = debug.getinfo(1, "S").source
    local dir = Aula.Path.getParentDirectory(filename:same("@", true, 1) and filename:sub(2) or filename)

    --- script file
    for _, ext in ipairs {".lua", ".sym", ".tl"} do
        local filepath = Aula.Path.appendSlash(dir) .. module_name .. ext
        local file = Aula.IO.File.new(filepath)

        if file:getState() == Aula.Object.State.ACTIVE then
            return filepath, file, nil
        end
        table.insert(tried, "no file '" .. filepath .. "'")
    end

    -- search from package.path
    for entry in package.path:gmatch("[^;]+") do 
        local filepath = Aula.Path.complete(entry:replace("?", module_name))
        local file = Aula.IO.File.new(filepath)

        if file:getState() == Aula.Object.State.ACTIVE then
            return filepath, file, nil
        end
        table.insert(tried, "no file '" .. filepath .. "'")
    end
    return nil, nil, tried
end

-- override teal.process
-- * support for Aula.IO.readFile
-- @returns {function, string} loader, error_message
function teal.process(filename, env)
    if env and env.loaded and env.loaded[filename] then
       return env.loaded[filename]
    end

    local input = Aula.IO.readFile(filename)
    if input:getSize() == 0 then
       return nil, "failed to read file: '" .. filename .. "'"
    end
 
    return teal.process_string(input:toString(), Aula.Path.getExtension(filename) ~= ".tl", env, filename)
end

-- @private filter warnings
local function filter_warnings(result)
    if not result.warnings then
        return
    end
    for i = #result.warnings, 1, -1 do
        local w = result.warnings[i]
        if teal.config._disabled_warnings_set[w.tag] then
            table.remove(result.warnings, i)
        elseif teal.config._warning_errors_set[w.tag] then
            local err = table.remove(result.warnings, i)
            table.insert(result.type_errors, err)
        end
    end
end

-- @private report errors
local function report_errors(category, errors)
    if not errors then
        return false
    end
    if #errors > 0 then
        local n = #errors
        teal.config.error_writer("========================================")
        teal.config.error_writer(n .. " " .. category .. (n ~= 1 and "s" or "") .. ":")
        for _, err in ipairs(errors) do
            teal.config.error_writer(err.filename .. ":" .. err.y .. ":" .. err.x .. ": " .. (err.msg or ""))
        end
        return true
    end
    return false
end

-- @private report all errors
local function report_all_errors(env, syntax_only)
    local any_syntax_err, any_type_err, any_warning
    for _, name in ipairs(env.loaded_order or {}) do
        local result = env.loaded[name]

        local syntax_err = report_errors("syntax error", result.syntax_errors)
        if syntax_err then
            any_syntax_err = true
        elseif not syntax_only then
            filter_warnings(teal.config, result)
            any_warning = report_errors("warning", result.warnings) or any_warning
            any_type_err = report_errors("error", result.type_errors) or any_type_err
        end
    end
    local ok = not (any_syntax_err or any_type_err)
    return ok, any_syntax_err, any_type_err, any_warning
end

-- transpile teal => lua code
-- @param {string} input: teal source code
--      - if <module_name> is nil: <input> is treated as file name
--      - else: <input> is treated as source code
-- @param {string|nil} module_name: source code name for displaying compile error
-- @param {table|nil} env (default: teal.package_loader_env): teal language system environment
-- @returns {string} lua_code
teal.transpile = function (input, module_name, env)
    if not env then
        if not teal.package_loader_env then
            -- initialize default teal language system environment
            teal.package_loader_env = teal.init_env(
                teal.config.strict_mode,
                teal.config.gen_compat,
                teal.config.gen_target,
                teal.config.init_env_modules
            )
        end
        env = teal.package_loader_env
    end

    local result, err
    
    if module_name then
        result, err = teal.process_string(input, false, env, module_name)
    else
        result, err = teal.process(input, env)
    end
    
    if err then
        error(err)
    end

    local _, syntax_err, type_err = report_all_errors(env, false)
    if syntax_err then
        os.exit(1)
    end
    if type_err then
        os.exit(1)
    end

    return teal.pretty_print_ast(result.ast)
end


--- overload lua standard load function ---

-- @param {string} filename
--     - `*.lua`: load as a lua code
--     - `*.sym`: load as a compiled lua byte code (mode must be set)
--     - `*.tl`:  load as a teal code
-- @param {string} mode (default: "bt"): {"b": バイナリモード, "t": テキストモード, "bt": バイナリ＋テキストモード}
-- @param {table} env (default: _ENV)
-- @returns {function, string} loader, error_message
function loadfile(filename, mode, env)
    local ext = Aula.Path.getExtension(filename)
    -- transpile teal => lua and load
    if ext == ".tl" then
        return load(teal.transpile(filename), "@" .. filename .. ".lua", mode, env)
    end
    -- load lua (plain source code / compiled byte-code)
    return load(Aula.IO.readFile(filename):toString(), "@" .. filename, mode, env)
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

-- package path for searching
package.path = "?;?.lua;?.sym;?.tl;?/main.lua;?/main.sym;?/main.tl;" .. package.path
package.cpath = "?;?.dll;?.so;" .. package.cpath

-- appendix loader for teal.search_module
table.insert(package.loaders, 1, function (modname)
    local filename, file, tried = teal.search_module(modname)
    if not filename then
        return "\n\t" .. table.concat(tried or {}, "\n\t")
    end
    
    local loader, err = loadfile(filename)
    if not loader then
        error(err)
    end
    return loader
end)

-- appendix simple loader for c library
-- * dynamic link library entry point:
--      + luaopen_{module_name}
--      + luaopen_module
table.insert(package.loaders, 2, function (modname)
    local err = ""

    -- search from relative path
    local filename = debug.getinfo(1, "S").source
    local dir = Aula.Path.getParentDirectory(filename:same("@", true, 1) and filename:sub(2) or filename)

    for _, ext in ipairs {"", ".dll", ".so"} do
        local filepath = Aula.Path.appendSlash(dir) .. modname .. ext

        if Aula.Path.isFile(filepath) then
            local loader = package.loadlib(filepath, "luaopen_" .. Aula.Path.getBaseStem(filepath))

            if not loader then
                loader = package.loadlib(filepath, "luaopen_module")
            end
            if not loader then
                error("entry point function not found in module file '" .. filepath .. "'.")
            end
            return loader
        end
        err = err .. "\n\tno file '" .. filepath .. "'"
    end

    -- search from package.cpath
    for entry in package.cpath:gmatch("[^;]+") do 
        local filepath = Aula.Path.complete(entry:replace("?", modname))

        if Aula.Path.isFile(filepath) then
            local loader = package.loadlib(filepath, "luaopen_" .. Aula.Path.getBaseStem(filepath))

            if not loader then
                loader = package.loadlib(filepath, "luaopen_module")
            end
            if not loader then
                error("entry point function not found in module file '" .. filepath .. "'.")
            end
            return loader
        else
            err = err .. "\n\tno file '" .. filepath .. "'"
        end
    end
    return err
end)


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
