-- compile lua => sym, and append sym to resource
-- @param {fs.zip.archive_t} zip
-- @param {string} luafile
-- @param {string} rootdir
local function append_bytecode(zip, luafile, rootdir)
    local resname = luafile:sub(rootdir:len() + 2):sub(1, -5)
    local f, err = load(fs.readfile(luafile):tostr(), "@aula://" .. resname)
    if f == nil then
        error(err)
    end

    local bytecode = string.dump(f)
    if not zip:append(io.binary_openstr(bytecode, bytecode:len()), resname .. ".sym") then
        errorf("failed to append %s", resname .. ".sym")
    end
    printf("%s.lua has been bundled into aula://%s.sym\n", resname, resname)
end

-- open aula application as archive
local aula = package.__dir .. "/aula" .. (ffi.os == "Windows" and ".exe" or "")
local zip = fs.zip.open(aula, "w+")

if zip == nil then
    errorf("failed to open '%s' as zip archive", aula)
end

-- append lua scripts as resource
local dir = package.__dir .. "/resource"

local function dir_scan(dir, callback)
    local dirent = fs.dir_open(dir)
    if not dirent then return false end
    repeat
        if dirent.current_name ~= "." and dirent.current_name ~= ".." then
            if not callback(dirent) then return false end
        end
    until not dirent:next()
    dirent:close()
    return true
end

local function bundle(dirent)
    if dirent.current_isdir then
        return dir_scan(dirent.current_path, bundle)
    end
    if fs.path.ext(dirent.current_path) == ".lua" then
        local filepath, _ = dirent.current_path:gsub("\\", "/")
        append_bytecode(zip, filepath, dir)
    end
    return true
end

dir_scan(dir, bundle)
