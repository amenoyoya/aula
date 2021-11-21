--[[ clean up previous garbage (case: previous test is failed) ]]
fs.rmdir(package.__dir .. "/iosample")
fs.rmdir(package.__dir .. "/iosample_copied")
fs.rmfile(package.__dir .. "/iosample.zip")


--[[ write file sample ]]
local file = fs.file_open(package.__dir .. "/iosample/sample.txt", "wb")
local text = [[
このファイルは fs.file_open で作成されたサンプルファイルです。
⭕ UTF-8 でコーディングされていれば文字化けすることなく作成されているはずです。]]

if file == nil then
    error"failed to create file 'iosample/sample.txt'"
end

file:write(io.binary_openstr(text), false) -- no crlf appendix
file:close() -- or file:flush()

-- test
assert(fs.readfile(package.__dir .. "/iosample/sample.txt"):tostr() == text)
print(fs.readfile(package.__dir .. "/iosample/sample.txt"):tostr())
printf("✅ OK: fs.file_t:write\n\tsample.txt: %s\n", text)


--[[ read file sample ]]
file = fs.file_open(package.__dir .. "/iosample/sample.txt")

if file == nil then
    error "failed to open file 'iosample/sample.txt'"
end

-- test
local lines = {
    file:readline(),
    file:readline()
}
assert(lines[1] == "このファイルは fs.file_open で作成されたサンプルファイルです。")
assert(lines[2] == "⭕ UTF-8 でコーディングされていれば文字化けすることなく作成されているはずです。")
printf("✅ OK: Aula.IO.File:readLine\n\t[1]: %s\n\t[2]: %s\n", lines[1], lines[2])

file:seek(0, io.seekfrom.head)
local filesize = file.size
local readtext = file:read(filesize):tostr()

file:seek(-file.size, io.seekfrom.tail)
local readbin = file:read(filesize)

assert(readtext == text)
assert(readbin:tostr() == readtext)
assert(readtext:len() == filesize)
printf("✅ OK: fs.file_t:read\n\tsize: %d\n\tcontent: %s\n", filesize, readtext)
file:close()


-- Error test
local errfile = fs.file_open("!!!")

assert(errfile == nil)
print "✅ OK: fs.file_open: failed to open file '!!!'"


-- FileSystem
assert(fs.copyfile(package.__dir .. "/iosample/sample.txt", package.__dir .. "/iosample/sample_copied.txt"))
assert(fs.path.isfile(package.__dir .. "/iosample/sample_copied.txt"))
print "✅ OK: fs.copyfile"

assert(fs.copydir(package.__dir .. "/iosample", package.__dir .. "/iosample_copied"))
assert(fs.copydir(package.__dir .. "/iosample_copied", package.__dir .. "/iosample/copied_directory"))

local file_count, dir_count = 0, 0
local dirlen = (package.__dir .. '/iosample/'):u8len()

for i, file in ipairs(fs.enumfiles(package.__dir .. "/iosample")) do
    print("\t" .. file.path:u8sub(dirlen + 1):replace('\\', '/'))
    if file.isfile then file_count = file_count + 1 end
    if file.isdir then dir_count = dir_count + 1 end
end
assert(file_count == 4)
assert(dir_count == 1)
print "✅ Check: fs.enumfiles (nested)"

file_count, dir_count = 0, 0
for i, file in ipairs(fs.enumfiles(package.__dir .. "/iosample", -1, "file")) do
    print("\t" .. file.path:u8sub(dirlen + 1):replace('\\', '/'))
    if file.isfile then file_count = file_count + 1 end
    if file.isdir then dir_count = dir_count + 1 end
end
assert(file_count == 4)
assert(dir_count == 0)
print "✅ Check: fs.enumfiels (file only)"

file_count, dir_count = 0, 0
for i, file in ipairs(fs.enumfiles(package.__dir .. "/iosample", 1)) do
    print("\t" .. file.path:u8sub(dirlen + 1):replace('\\', '/'))
    if file.isfile then file_count = file_count + 1 end
    if file.isdir then dir_count = dir_count + 1 end
end
assert(file_count == 2)
assert(dir_count == 1)
print "✅ Check: fs.enumfiles (not nested)"

assert(fs.rmdir(package.__dir .. "/iosample_copied"))
print "✅ Check: fs.rmdir"

require "./zip" -- require {__dir}/zip.lua
