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


--- extended teal ---

-- teal configuration
-- * change this table if you want to change teal behavior
teal.config = {
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
-- * support for getting current script info
local original_teal_process_string = teal.process_string

function teal.process_string(input, is_lua, env, filename)
    package.__chunk = filename
    package.__dir = filename and Aula.Path.getParentDirectory(filename:same("@", true, 1) and filename:sub(2) or filename)
    return original_teal_process_string(
        input:sub(1, 3) == "\xEF\xBB\xBF" and input:sub(4) or input,
        is_lua,
        env,
        filename
    )
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
                false,
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
