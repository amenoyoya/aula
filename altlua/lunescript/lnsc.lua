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
    -- case: os.argv[2] is "*.lns" file
    -- => execute lunescript (project directory is parent directory of the file)
    if Aula.Path.isFile(os.argv[2]) and Aula.Path.getExtension(os.argv[2]) == ".lns" then
        return lune_script(os.argv[2], unpack(os.argv, 4))
    end

    -- case: os.argv[2] is "test"
    -- => execute "*_test.lns" files in os.argv[3] to test
    if os.argv[2] == "test" then
        local cntOK, cntNG = 0, 0 -- count of test results
        local testStart = os.systime() -- measure execution time

        for _, file in ipairs(Aula.IO.enumerateFiles(os.argv[3] or ".", -1, Aula.IO.EnumFileOption.FILE)) do
            if file.path:match("_test%.lns$") then
                local start = os.systime()
                local result, err = pcall(lune_script, file.path)

                if result then -- OK
                    printf("✅ %s (%d ms)\n", file.path, os.systime() - start)
                    cntOK = cntOK + 1
                else -- NG
                    printf("❌ %s (%d ms)\n", file.path, os.systime() - start)
                    print(err)
                    cntNG = cntNG + 1
                end
            end
        end
        -- display test summary
        printf("\nTests:\t%d failed, %d total\n", cntNG, cntOK + cntNG)
        printf("Time:\t%d ms\n\n", os.systime() - testStart)
        return nil
    end

    -- case: default
    return lune_cli(unpack(os.argv, 2))
end

lune_main()
