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
