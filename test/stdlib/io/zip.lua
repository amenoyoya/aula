--[[ create zip archive sample ]]
assert(Zip.compress(package.__dir .. "/iosample", package.__dir .. "/iosample.zip"))
print "✅ OK: Zip.compress: iosample/ => iosample.zip"

--[[ read zip archive sample ]]
local zip = Zip.Archiver.new(package.__dir .. "/iosample.zip", "r")

assert(zip:getState() ~= Object.State.FAILED)
assert(zip:toFirstFile())

print "✅ OK: Zip.Archiver:open-getCurrentFileInformation"
repeat
    local info = zip:getCurrentFileInformation(true)
    printf("\t%s: %s\n", info.fileName, info.uncompressedData:toString())
until not zip:toNextFile()
zip:close()

assert(IO.removeDirectory(package.__dir .. "/iosample"))
assert(IO.removeFile(package.__dir .. "/iosample.zip"))
assert(not Path.isDirectory(package.__dir .. "/iosample"))
assert(not Path.isFile(package.__dir .. "/iosample.zip"))
print "✅ OK: Aula.IO.removeDirectory, Aula.IO.removeFile"
