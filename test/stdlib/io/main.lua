using(Aula) -- Aula.* => _GLOBAL.*

--[[ clean up previous garbage ]]
IO.removeDirectory(__dir() .. "/iosample")
IO.removeFile(__dir() .. "/iosample.zip")


--[[ write file sample ]]
local file = IO.File.new(__dir() .. "/iosample/sample.txt", "wb")
local text = [[
このファイルは Aula.IO.File に作成されたサンプルファイルです。
⭕ UTF-8 でコーディングされていれば文字化けすることなく作成されているはずです。]]

if file:getState() == Object.State.FAILED then
    error(file:getMessage())
end

file:write(text, false) -- no crlf appendix
file:close() -- or file:flush()

-- test
print(IO.readFile(__dir() .. "/iosample/sample.txt"):toString())
assert(IO.readFile(__dir() .. "/iosample/sample.txt"):toString() == text)
printf("✅ OK: Aula.IO.File:write\n\tsample.txt: %s\n", text)


--[[ read file sample ]]
file = IO.File.new(__dir() .. "/iosample/sample.txt")

if file:getState() == Object.State.FAILED then
    error(file:getMessage())
end

-- test
local lines = {
    file:readLine(),
    file:readLine()
}
assert(lines[1] == "このファイルは Aula.IO.File に作成されたサンプルファイルです。")
assert(lines[2] == "⭕ UTF-8 でコーディングされていれば文字化けすることなく作成されているはずです。")
printf("✅ OK: Aula.IO.File:readLine\n\t[1]: %s\n\t[2]: %s\n", lines[1], lines[2])

file:seek(0, IO.SeekFrom.HEAD)
local filesize = file:getSize()
local readtext = file:readString(filesize)

file:seek(-file:getSize(), IO.SeekFrom.END)
local readbin = file:read(filesize)

assert(readtext == text)
assert(readbin:toString() == readtext)
assert(readtext:len() == filesize)
printf("✅ OK: Aula.IO.File:read\n\tsize: %d\n\tcontent: %s\n", filesize, readtext)


-- Error test
local errfile = IO.File.new("!!!")

assert(errfile:getState() == Object.State.FAILED)
printf("✅ OK: Aula.IO.File.open: %s\n", errfile:getMessage())


-- FileSystem
assert(IO.copyFile(__dir() .. "/iosample/sample.txt", __dir() .. "/iosample/sample_copied.txt"))
assert(file:open(__dir() .. "/iosample/sample_copied.txt", "r"))
file:close()
print "✅ OK: Aula.IO.copyFile"

assert(IO.copyDirectory(__dir() .. "/iosample", __dir() .. "/iosample/copied_directory"))

local files = {
    "copied_directory",
    "copied_directory/sample.txt",
    "copied_directory/sample_copied.txt",
    "sample.txt",
    "sample_copied.txt"
}
local dirlen = (__dir() .. '/iosample/'):u8len()

print "✅ Check: Aula.IO.enumerateFiles (nested)"
for i, file in ipairs(IO.enumerateFiles(__dir() .. "/iosample")) do
    file = file.path:u8sub(dirlen + 1):replace('\\', '/')
    print("\t" .. file)
    assert(file == files[i])
end

print "✅ Check: Aula.IO.enumerateFiles (file only)"
for i, file in ipairs(IO.enumerateFiles(__dir() .. "/iosample", -1, Aula.IO.EnumFileOption.FILE)) do
    file = file.path:u8sub(dirlen + 1):replace('\\', '/')
    print("\t" .. file)
    assert(file == files[i + 1])
end

table.remove(files, 3)
table.remove(files, 2)
print "✅ Check: Aula.IO.enumerateFiles (not nested)"
for i, file in ipairs(IO.enumerateFiles(__dir() .. "/iosample", 1)) do
    file = file.path:u8sub(dirlen + 1):replace('\\', '/')
    print("\t" .. file)
    assert(file == files[i])
end

include "zip" -- require {__dir}/zip.lua
