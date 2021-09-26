local u8str = 'Hello, ルア！'

print(Aula.Encoding.getEncodingName(u8str))
-- print(u8str) -- windows 環境では文字化けする
Aula.IO.Stdout:write(u8str)

-- Error test
local errfile = Aula.IO.File.new("!!!")

if errfile:getState() == Aula.Object.State.FAILED then
    Aula.IO.Stderr:write(errfile:getMessage())
end

-- FileSystem
local file = Aula.IO.File.new("sample/test.txt", "w")

if file:getState() == Aula.Object.State.FAILED then
    error(file:getMessage())
end

local text = 'バイナリサンプル'
local bin = Aula.IO.Binary.new()
bin:pushString(text, text:len())
Aula.IO.Stdout:write(bin:toString(0))

local writtenSize = file:write(bin, bin:getSize())

Aula.IO.Stdout:write("sample/test.txt: " .. writtenSize .. " bytes have been written")
file:flush()

if not Aula.IO.copyFile("sample/test.txt", "sample/test_copied.txt", true) then
    error("failed to copy: sample/test.txt => sample/test_copied.txt")
end

if not file:open("sample/test_copied.txt", "r") then
    error(file:getMessage())
end

Aula.IO.Stdout:write(file:read(file:getSize(), 1):toString(0))