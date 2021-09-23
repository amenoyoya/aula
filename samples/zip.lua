using(Aula)

--[[ create zip archive sample ]]
if not compressDirectory(".", "./sample.zip") then
    error("Cannot compress current directory")
end

--[[ read zip archive sample ]]
local zip = ZipArchiver("./sample.zip", "r")

if getState(zip) == Object.FAILED or not zip:toFirstFile() then
    error("Cannot open ./sample.zip")
end

println("Completed to create: ./sample.zip")

repeat
    local info = ZipFileInformation()
    if zip:getCurrentFileInformation(info) then
        println(info.fileName)
    end
until not zip:toNextFile()
