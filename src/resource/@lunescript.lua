local function lune_cli(...)
    local arg = {...}
    table.insert(arg, 1, "")
    require('lune.base.front').exec(arg)
end

local function lune_script(filepath, ...)
    local filename = Aula.Path.getBaseName(filepath)
    local projdir, _ = Aula.Path.getParentDirectory(filepath):gsub("\\", "/")
    local args = { filename, os.argv[3] or "exe", "--projDir", projdir }

    for i, argv in ipairs{...} do
        args[i + 4] = argv
    end
    lune_cli(unpack(args))
end

local function lune_main()
    -- case: no arguments
    -- => display lunescript cli help
    if #os.argv < 3 then
        return lune_cli("help")
    end

    -- case: os.argv[2] is "*.lns" file
    -- => execute lunescript (project directory is parent directory of the file)
    if Aula.Path.isFile(os.argv[2]) and Aula.Path.getExtension(os.argv[2]) == ".lns" then
        return lune_script(os.argv[2], unpack(os.argv, 4))
    end

    -- case: default
    return lune_cli(unpack(os.argv, 2))
end

-- LuneScript use `loadstring`
loadstring = load

return {
    dofile = lune_script,
    exec = lune_main,
}
