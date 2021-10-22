require(__dir() .. "/system")

-- initialize Teal environment
local tlconfig = {
    strict_mode = true,
    gen_compat = "required", -- "off" | "optional" | "required"
    gen_target = "5.1", -- "5.1" | "5.3"
    init_env_modules = {}, -- initial loaded modules
    _disabled_warnings_set = {},
    _warning_errors_set = {},
}

local env, err = teal.init_env(not tlconfig.strict_mode, tlconfig.gen_compat, tlconfig.gen_target, tlconfig.init_env_modules)

if not env then
    error(err)
end

-- override teal.process_string
-- function teal.process_string(input, is_lua, env, filename)
--     env = env or teal.init_env(is_lua)
--     if env.loaded and env.loaded[filename] then
--        return env.loaded[filename]
--     end
--     filename = filename or ""
 
--     local syntax_errors = {}
--     local tokens, errs = teal.lex(
--         input:sub(1, 3) == "\xEF\xBB\xBF" and input:sub(4) or input
--     )
--     if errs then
--        for _, err in ipairs(errs) do
--           table.insert(syntax_errors, {
--             y = err.y,
--             x = err.x,
--             msg = "invalid token '" .. err.tk .. "'",
--             filename = filename,
--           })
--        end
--     end
 
--     local _, program = teal.parse_program(tokens, syntax_errors, filename)
 
--     if (not env.keep_going) and #syntax_errors > 0 then
--        local result = {
--           ok = false,
--           filename = filename,
--           type_errors = {},
--           syntax_errors = syntax_errors,
--           env = env,
--        }
--        env.loaded[filename] = result
--        table.insert(env.loaded_order, filename)
--        return result
--     end
 
--     local opts = {
--        filename = filename,
--        lax = is_lua,
--        gen_compat = env.gen_compat,
--        env = env,
--     }
--     return teal.type_check(program, opts)
-- end

-- -- override teal.search_module
-- function teal.search_module(module_name, search_dtl)
--     local tried = {}
    
--     for _, path in ipairs(package.libpath) do
--         local filepath = Aula.Path.complete(path:replace("?", module_name))

--         if Aula.Path.isFile(filepath) then
--             return filepath, Aula.IO.File.new(filepath)
--         end
--         table.insert(tried, "no file '" .. filepath .. "'")
--     end
--     return nil, nil, tried
-- end

-- -- override teal.process
-- function teal.process(filename, env)
--     if env and env.loaded and env.loaded[filename] then
--         print("loaded", filename)
--        return env.loaded[filename]
--     end
    
--     local input = Aula.IO.readFile(filename)
--     if input:getSize() == 0 then
--        return nil, "no script code in \"" .. filename .. "\""
--     end
--     env.loaded[filename] = teal.process_string(input:toString(), Aula.Path.getExtension(filename) ~= ".tl", env, filename)
--     return env.loaded[filename]
-- end

-- filter warnings
local function filter_warnings(tlconfig, result)
    if not result.warnings then
       return
    end
    for i = #result.warnings, 1, -1 do
       local w = result.warnings[i]
       if tlconfig._disabled_warnings_set[w.tag] then
          table.remove(result.warnings, i)
       elseif tlconfig._warning_errors_set[w.tag] then
          local err = table.remove(result.warnings, i)
          table.insert(result.type_errors, err)
       end
    end
end

-- report errors
local function report_errors(category, errors)
    if not errors then
       return false
    end
    if #errors > 0 then
       local n = #errors
       Aula.IO.Stderr:write("========================================")
       Aula.IO.Stderr:write(n .. " " .. category .. (n ~= 1 and "s" or "") .. ":")
       for _, err in ipairs(errors) do
          Aula.IO.Stderr:write(err.filename .. ":" .. err.y .. ":" .. err.x .. ": " .. (err.msg or ""))
       end
       return true
    end
    return false
end

-- report all errors
local function report_all_errors(tlconfig, env, syntax_only)
    local any_syntax_err, any_type_err, any_warning
    for _, name in ipairs(env.loaded_order) do
       local result = env.loaded[name]

       local syntax_err = report_errors("syntax error", result.syntax_errors)
       if syntax_err then
          any_syntax_err = true
       elseif not syntax_only then
          filter_warnings(tlconfig, result)
          any_warning = report_errors("warning", result.warnings) or any_warning
          any_type_err = report_errors("error", result.type_errors) or any_type_err
       end
    end
    local ok = not (any_syntax_err or any_type_err)
    return ok, any_syntax_err, any_type_err, any_warning
end

-- check and load Teal script
local function check_and_load(filename, env, tlconfig)
    local result, err = teal.process(filename, env)
    if err then
        error(err)
    end
    local _, syntax_err, type_err = report_all_errors(tlconfig, env, false)
    if syntax_err then
        -- os.exit(1)
        print"syntax error"
    end

    if type_err then
        -- os.exit(1)
        print"type error"
    end

    local chunk, err = load(teal.pretty_print_ast(result.ast), "@./main.tl")
    if err then
        error(
            "Internal Compiler Error: Teal generator produced invalid Lua. " ..
            "Please report a bug at https://github.com/teal-language/tl\n\n" .. tostring(err)
        )
    end

    return chunk
end

-- main.tl
-- os.setenv("TL_PATH", "?.tl;" .. __dir() .. "/?.tl")
-- teal.loader()
-- table.insert(
--     package.loaders,
--     1,
--     function (filename)
--         local filepath = Aula.Path.complete(filename .. ".tl")

--         if Aula.Path.isFile(filepath) then
--             return check_and_load(filepath, env, tlconfig)
--         end
--         return "module not found: '"..filepath.."'"
--     end
-- )
assert(check_and_load(__dir() .. "/main.tl", env, tlconfig))()
