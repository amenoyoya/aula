local u8str = 'Hello, ルア！'

print(Aula.Encoding.getEncodingName(u8str))
-- print(u8str) -- windows 環境では文字化けする
Aula.Console.writeLine(u8str)

-- FileSystem
local cppfile = Aula.File.new("sol_core.cpp")
local luafile = Aula.File.new("sol_core.lua")

Aula.Console.writeLine("sol_core.cpp: "..cppfile:getSize())
Aula.Console.writeLine("sol_core.lua: "..luafile:getSize())

if cppfile:open("sol_core.exe", "r") then
    if luafile:open(cppfile:getHandle(), 0) then
        Aula.Console.writeLine("sol_core.exe: "..luafile:getSize())
    end
end