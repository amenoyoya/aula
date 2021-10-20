local luacode = Aula.IO.readFile(__dir() .. "/resource/main.lua")
local f, err = load(luacode:toString(), "@<aula/main>")

if f == nil then
    error(err)
end

local bytecode = string.dump(f)
local aula = __dir() .. "/aula" .. (ffi.os == "Windows" and ".exe" or "")
local arc = Aula.Zip.Archiver.new(aula, "w+")

if arc:getState() == Aula.Object.State.FAILED then
    error(arc:getMessage())
end

if not arc:append(Aula.IO.Binary.new(bytecode, bytecode:len()), "main.sym") then
    error("failed to append main.sym")
end

print"resource/main.lua has been bundled into aula/main.sym"
