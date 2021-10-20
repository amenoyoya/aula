local function compile(infile, outfile, chunkname)
    print("compile: "..infile)
    
    local fh, msg = io.open(infile, "r")
    if not (fh) then
        error(msg)
    end

    local func = assert(load(fh:read"*a", chunkname))
    local dump, data = string.dump(func), ""
    for i = 1, dump:len() do
        data = data..dump:byte(i, i)..","
    end
    fh:close()
    fh, msg = io.open(outfile, "w")
    if not (fh) then
        error(msg)
    end
    fh:write(data)
    fh:close()
end

compile("teal.lua", "teal.cpp", "<stdlib/teal>")
compile("string.lua", "string.cpp", "<stdlib/string>")
compile("table.lua", "table.cpp", "<stdlib/table>")
compile("lpeg.lua", "lpeg.cpp", "<stdlib/lpeg>")
compile("system.lua", "system.cpp", "<stdlib/system>")

-- ライブラリのロード順
--[[
    1. teal
    2. string
    3. table
    4. lpeg
    5. system
]]