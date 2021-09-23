local function compile(infile, outfile, chunkname)
    print("compile: "..infile)
    
    local fh, msg = io.open(infile, "r")
    if not (fh) then
        error(msg)
    end

    local func = assert(loadstring(fh:read"*a", chunkname))
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

compile("LPeg.lua", "LPeg.cpp", "<Aula/Core/LPeg>")
compile("Main.lua", "Main.cpp", "<Aula/Core/Main>")
compile("String.lua", "String.cpp", "<Aula/Core/String>")
compile("Table.lua", "Table.cpp", "<Aula/Core/Table>")