--- extended teal ---

-- teal configuration
-- * change this table if you want to change teal behavior
teal.config = {
    gen_compat = "required", -- "off" | "optional" | "required"
    gen_target = "5.1", -- "5.1" | "5.3"
    init_env_modules = {}, -- initial loaded modules
    syntax_only = false, -- true: check only syntax error
    _disabled_warnings_set = {},
    _warning_errors_set = {},
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
        Aula.IO.Stderr:write "========================================"
        Aula.IO.Stderr:write(n .. " " .. category .. (n ~= 1 and "s" or "") .. ":")
        for _, err in ipairs(errors) do
            Aula.IO.Stderr:write(err.filename .. ":" .. err.y .. ":" .. err.x .. ": " .. (err.msg or ""))
        end
        Aula.IO.Stderr:write "" -- \n
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
-- @returns {string|nil, string|nil} lua_code, error_message
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
        return nil, err
    end

    local _, syntax_err, type_err = report_all_errors(env, teal.config.syntax_only)
    if syntax_err then
        return nil, "syntax error in '" .. (module_name or input) .. "'"
    end
    if type_err then
        return nil, "type error in '" .. (module_name or input) .. "'"
    end

    return teal.pretty_print_ast(result.ast)
end


--- overload lua standard load function ---

-- override load
local original_load = load

-- * support for getting current script info
-- @param {string} code
-- @param {string} chunkname
-- @param {string} mode (default: "bt"): {"b": binary mode, "t": text mode, "bt": binary + text mode}
-- @param {table} env (default: _ENV)
-- @returns {function, string} loader, error_message
function load(code, chunkname, mode, env)
    local f, err = original_load(code, chunkname, mode, env)
    if f == nil then
        return f, err
    end
    return function()
        -- store previous package.__chunk, package.__dir
        local __chunk = package.__chunk
        local __dir = package.__dir
        -- enable to get current script info from package.__chunk, package.__dir
        package.__chunk = chunkname
        package.__dir = chunkname and Aula.Path.getParentDirectory(chunkname:same("@", true, 1) and chunkname:sub(2) or chunkname)
        
        local result = f()
        -- restore package.__chunk, package.__dir
        package.__chunk = __chunk
        package.__dir = __dir

        return result
    end, err
end

-- override loadfile
-- @param {string} filename
--     - `*.lua`: load as a lua code
--     - `*.sym`: load as a compiled lua byte code (mode must be set)
--     - `*.tl`:  load as a teal code
-- @param {string} mode (default: "bt")
-- @param {table} env (default: _ENV)
-- @returns {function|nil, string} loader, error_message
function loadfile(filename, mode, env)
    local ext = Aula.Path.getExtension(filename)
    -- transpile teal => lua and load
    if ext == ".tl" then
        local luacode, err = teal.transpile(filename)
        
        if luacode == nil then
            return nil, err
        end
        return load(luacode, "@" .. filename .. ".lua", mode, env)
    end
    -- load lua (plain source code / compiled byte-code)
    return load(Aula.IO.readFile(filename):toString(), "@" .. filename, mode, env)
end

-- override dofile
-- @param {string} filename
function dofile(filename)
    local f, err = loadfile(filename)
    if not f then
        error(err)
    end
    return f()
end


--- extended package.loaders ---

-- override teal.search_module
-- * support for simple package searching system
-- @returns {string, userdata, table} module_name, file_handler( has :close() method ), errors
function teal.search_module(module_name, search_dtl)
    local tried = {}
    
    -- search from relative path
    if package.__dir then
        for _, ext in ipairs {"", ".lua", ".sym", ".tl", "/init.lua", "/init.sym", "/init.tl"} do
            local filepath = Aula.Path.appendSlash(package.__dir) .. module_name .. ext
            local file = Aula.IO.File.new(filepath)

            if file:getState() == Aula.Object.State.ACTIVE then
                return filepath, file, nil
            end
            table.insert(tried, "no file '" .. filepath .. "'")
        end
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

-- package path for searching
package.path = "?;?.lua;?.sym;?.tl;?/init.lua;?/init.sym;?/init.tl;" .. package.path
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
    if package.__dir then
        for _, ext in ipairs {"", ".dll", ".so"} do
            local filepath = Aula.Path.appendSlash(package.__dir) .. modname .. ext

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
