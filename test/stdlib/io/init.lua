using(Aula) -- Aula.* => _GLOBAL.*

--[[ clean up previous garbage ]]
IO.removeDirectory(package.__dir .. "/iosample")
IO.removeFile(package.__dir .. "/iosample.zip")


--[[ write file sample ]]
local file = IO.File.new(package.__dir .. "/iosample/sample.txt", "wb")
local text = [[
このファイルは Aula.IO.File に作成されたサンプルファイルです。
⭕ UTF-8 でコーディングされていれば文字化けすることなく作成されているはずです。]]

if file:getState() == Object.State.FAILED then
    error(file:getMessage())
end

file:write(text, false) -- no crlf appendix
file:close() -- or file:flush()

-- test
print(IO.readFile(package.__dir .. "/iosample/sample.txt"):toString())
assert(IO.readFile(package.__dir .. "/iosample/sample.txt"):toString() == text)
printf("✅ OK: Aula.IO.File:write\n\tsample.txt: %s\n", text)


--[[ read file sample ]]
file = IO.File.new(package.__dir .. "/iosample/sample.txt")

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
assert(IO.copyFile(package.__dir .. "/iosample/sample.txt", package.__dir .. "/iosample/sample_copied.txt"))
assert(file:open(package.__dir .. "/iosample/sample_copied.txt", "r"))
file:close()
print "✅ OK: Aula.IO.copyFile"

assert(IO.copyDirectory(package.__dir .. "/iosample", package.__dir .. "/iosample_copied"))
assert(IO.moveDirectory(package.__dir .. "/iosample_copied", package.__dir .. "/iosample/copied_directory"))

local file_count, dir_count = 0, 0
local dirlen = (package.__dir .. '/iosample/'):u8len()

for i, file in ipairs(IO.enumerateFiles(package.__dir .. "/iosample")) do
    print("\t" .. file.path:u8sub(dirlen + 1):replace('\\', '/'))
    if file.isFile then file_count = file_count + 1 end
    if file.isDirectory then dir_count = dir_count + 1 end
end
assert(file_count == 4)
assert(dir_count == 1)
print "✅ Check: Aula.IO.enumerateFiles (nested)"

file_count, dir_count = 0, 0
for i, file in ipairs(IO.enumerateFiles(package.__dir .. "/iosample", -1, Aula.IO.EnumFileOption.FILE)) do
    print("\t" .. file.path:u8sub(dirlen + 1):replace('\\', '/'))
    if file.isFile then file_count = file_count + 1 end
    if file.isDirectory then dir_count = dir_count + 1 end
end
assert(file_count == 4)
assert(dir_count == 0)
print "✅ Check: Aula.IO.enumerateFiles (file only)"

file_count, dir_count = 0, 0
for i, file in ipairs(IO.enumerateFiles(package.__dir .. "/iosample", 1)) do
    print("\t" .. file.path:u8sub(dirlen + 1):replace('\\', '/'))
    if file.isFile then file_count = file_count + 1 end
    if file.isDirectory then dir_count = dir_count + 1 end
end
assert(file_count == 2)
assert(dir_count == 1)
print "✅ Check: Aula.IO.enumerateFiles (not nested)"

require "./zip" -- require {__dir}/zip.lua
