-- version
Aula.version = "v1.3.1"

-- help text
local helpText = [==[
Aula is a Lua script engine.

Usage:
    aula [command] [script_file] [arguments]
    
The commands are:
    help        display information about Aula script engine
    version     display Aula version
    transpile   transpile Teal code to Lua code
            Usage:          $ aula transpile <input_teal_script_file> <output_lua_script_file>
            Description:    Aula will transpile <input_teal_script_file> to <output_lua_script_file>
    compile     compile Lua / Teal code to byte-code
            Usage:          $ aula compile <input_lua_script_file> <output_byte_code_file>
            Description:    Aula will compile <input_lua_script_file> to <output_byte_code_file>
    test        execute test codes
            Usage:          $ aula test [directory (default: ./)]
            Description:    Aula will execute test script files like "*_test.lua", "*_test.tl" in the <directory> and the sub directories

The script file will be executed:
    If the "main.lua" file exists at the directory containing Aula: execute a plain Lua script file
    Or if the "main.sym" file exists at the directory containing Aula: execute a compiled Lua byte-code file
    Or if the "main.tl" file exists at the directory containing Aula: execute a Teal script file
    Or if the command line arguments[1] is "*.lua" file: execute a plain Lua script file
    Or if the command line arguments[1] is "*.sym" file: execute a ompiled Lua byte-code file
    Or if the command line arguments[1] is "*.tl" file: execute a Teal script file
    
    
Aula will be executed as interactive-mode if there are no commands and script files.
]==]

-- print version info
local function printVersion()
    printf("Aula Engine %s -- Copyright (C) 2021 amenoyoya. https://github.com/amenoyoya/aula\n", Aula.version)
    printf("%s -- Copyright (C) 2005-2017 Mike Pall. http://luajit.org/\n", jit.version)
end

-- os.argv[0] <= The Aula engine path
os.argv[0] = os.argv[1]
table.remove(os.argv, 1)

-- package path for searching
package.path = "?.lua;?.sym;?.tl;?/init.lua;?/init.sym;?/init.tl;" .. package.path
package.cpath = "?.dll;?.so;" .. package.cpath

-- extended package loader: search from current application (os.arv[0]) resource
table.insert(package.loaders, 1, function (module_name)
    local arc = Aula.Zip.Archiver.new(os.argv[0], "r")
    if arc:getState() == Aula.Object.State.FAILED then
        return "\n\tcurrent application has no resource: '" .. os.argv[0] .. "'"
    end

    local error_message = ""
    module_name = module_name:gsub("%.", "/") -- "." => "/"

    for entry in package.path:gmatch("[^;]+") do
        if arc:locateFile(entry:replace("?", module_name)) then
            local info = arc:getCurrentFileInformation(true)

            if info.uncompressedData:getSize() > 0 then
                arc:close()
                
                local loader, err = load(info.uncompressedData:toString(), "@aula://" .. module_name)
                if loader == nil then
                    error(err)
                end
                return loader
            end
        end
        error_message = error_message .. "\n\tno file 'aula://" .. module_name .. "'"
    end
    arc:close()
    return error_message
end)

-- require aula://@system
-- * teal language system
-- * relative require package system
require "@system"

-- CLI commands
local commands = {
    help = function ()
        print(helpText)
    end,
    
    version = function ()
        printVersion()
    end,

    transpile = function ()
        local input, output = os.argv[2], os.argv[3]

        if input == nil or not Aula.Path.isFile(input) then
            error("no Teal script file is input")
        end
        if output == nil then
            error("no output Lua script file path is specified")
        end

        local code, err = teal.transpile(Aula.IO.readFile(input):toString(), input)
        if code == nil then
            error(err)
        end
        if not Aula.IO.writeFile(output, Aula.IO.Binary.new(code, code:len())) then
            errorf("cannot write Lua script into \"%s\"", output)
        end
    end,

    compile = function ()
        local input, output = os.argv[2], os.argv[3]

        if input == nil or not Aula.Path.isFile(input) then
            error("no Lua script file is input")
        end
        if output == nil then
            error("no output Lua byte-code file path is specified")
        end

        local f, err = loadfile(input)
        if f == nil then
            error(err)
        end

        local code = string.dump(f)
        if not Aula.IO.writeFile(output, Aula.IO.Binary.new(code, code:len())) then
            errorf("cannot write Lua byte-code into \"%s\"", output)
        end
    end,

    test = function ()
        -- Execute test codes like "*_test.lua" in the target directory or current directory, and measure execution time
        local files = Aula.IO.enumerateFiles(os.argv[2] or ".", -1, Aula.IO.EnumFileOption.FILE)
        local cntOK, cntNG = 0, 0 -- count of test results
        local testStart = os.systime() -- measure execution time

        for _, file in ipairs(files) do
            if file.path:match("_test%.lua$") == nil and file.path:match("_test%.tl$") == nil then
                goto next
            end

            -- test code execution time
            local start = os.systime()
            local f, err = loadfile(file.path)

            if f then
                local result, err = pcall(f, "@" .. file.path)

                if result then -- OK
                    printf("✅ %s (%d ms)\n", file.path, os.systime() - start)
                    cntOK = cntOK + 1
                else -- NG
                    printf("❌ %s (%d ms)\n", file.path, os.systime() - start)
                    print(err)
                    cntNG = cntNG + 1
                end
            else -- syntax error
                printf("❌ %s (%d ms)\n", file.path, os.systime() - start)
                print(err)
                cntNG = cntNG + 1
            end
            ::next::
        end
        -- display test summary
        printf("\nTests:\t%d failed, %d total\n", cntNG, cntOK + cntNG)
        printf("Time:\t%d ms\n\n", os.systime() - testStart)
    end,
}

-- case: argv[1] is CLI commands
local f = commands[os.argv[1]]

if f then
    f()
    os.exit(0)
end

-- case: "{__dir}/main.lua" or "{__dir}/main.sym" or "{__dir}/main.tl" script file exists
local dir = Aula.Path.appendSlash(Aula.Path.getParentDirectory(os.argv[0]))
local function doMainScript(scriptFile)
    if Aula.Path.isFile(scriptFile) then
        table.insert(os.argv, 1, scriptFile) -- os.argv[1] <= main script file
        dofile(scriptFile)
        os.exit(0)
    end
end

doMainScript(dir .. "main.lua")
doMainScript(dir .. "main.sym")
doMainScript(dir .. "main.tl")

-- case: argv[1] is "*.lua" or "*.sym" or "*.tl" script file
local scriptFile = os.argv[1]

if scriptFile then
    local ext = Aula.Path.getExtension(scriptFile)

    if (ext == ".lua" or ext == ".sym" or ext == ".tl") and Aula.Path.isFile(scriptFile) then
        dofile(scriptFile)
        os.exit(0)
    end
end

-- case: no main script file exists
--- => execute interactive-mode
printVersion()
debug.debug(os.argv[0])
