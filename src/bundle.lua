-- compile resources
local function compileResource(name)
    local f, err = load(Aula.IO.readFile(package.__dir .. "/resource/" .. name .. ".lua"):toString(), "@aula://" .. name)
    if f == nil then
        error(err)
    end
    return f
end

local main = compileResource "main"
local system = compileResource "@system"
local compat53 = compileResource "compat53"
local compat53module = compileResource "compat53.module"

-- open aula application as archive
local aula = package.__dir .. "/aula" .. (ffi.os == "Windows" and ".exe" or "")
local arc = Aula.Zip.Archiver.new(aula, "w+")

if arc:getState() == Aula.Object.State.FAILED then
    error(arc:getMessage())
end

-- append resources
local function appendResource(arc, data, name)
    local bytecode = string.dump(data)
    if not arc:append(Aula.IO.Binary.new(bytecode, bytecode:len()), name .. ".sym") then
        errorf("failed to append %s.sym", name)
    end
    printf("resource/%s.lua has been bundled into aula://%s.sym\n", name, name)
end

appendResource(arc, main, "main")
appendResource(arc, system, "@system")
appendResource(arc, compat53, "compat53")
appendResource(arc, compat53module, "compat53.module")
