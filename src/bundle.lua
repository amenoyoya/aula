-- compile lua => sym, and append sym to resource
-- @param {Aula.Zip.Archiver} arc
-- @param {string} luafile
-- @param {string} rootdir
local function appendLuaToResource(arc, luafile, rootdir)
    local resname = luafile:sub(rootdir:len() + 2):sub(1, -5)
    local f, err = load(Aula.IO.readFile(luafile):toString(), "@aula://" .. resname)
    if f == nil then
        error(err)
    end
    
    local bytecode = string.dump(f)
    if not arc:append(Aula.IO.Binary.new(bytecode, bytecode:len()), resname .. ".sym") then
        errorf("failed to append %s", resname .. ".sym")
    end
    printf("%s.lua has been bundled into aula://%s.sym\n", resname, resname)
end

-- open aula application as archive
local aula = package.__dir .. "/aula" .. (ffi.os == "Windows" and ".exe" or "")
local arc = Aula.Zip.Archiver.new(aula, "w+")

if arc:getState() == Aula.Object.State.FAILED then
    error(arc:getMessage())
end

-- append lua scripts as resource
local dir = package.__dir .. "/resource"
local files = Aula.IO.enumerateFiles(dir)

for _, file in ipairs(files) do
    if Aula.Path.getExtension(file.path) == ".lua" then
        local filepath, _ = file.path:gsub("\\", "/")
        appendLuaToResource(arc, filepath, dir)
    end
end
