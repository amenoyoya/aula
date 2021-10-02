using(Aula)

--[[ write file sample ]]
local file = File("file.sample.txt", "w")

if getState(file) == Object.FAILED then
    error(getMessage(file))
end

file:write [[
このファイルは file.lua に作成されたサンプルファイルです。
UTF-8 でコーディングされていれば文字化けすることなく作成されているはずです。
]]

file:close() -- or file:flush()

--[[ read file sample ]]
file = File("file.sample.txt")

if getState(file) == Object.FAILED then
    error(getMessage(file))
end

printf("file size: %d\n%s", file:getSize(), file:read(file:getSize()))

--[[ enumerate files sample ]]
for _, file in ipairs(enumerateFiles("..", 2)) do
    print(file)
end
