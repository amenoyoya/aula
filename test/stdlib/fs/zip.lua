--[[ create zip archive sample ]]
assert(fs.zip.compress(package.__dir .. "/iosample", package.__dir .. "/iosample.zip"))
print "✅ OK: fs.zip.compress: iosample/ => iosample.zip"

--[[ read zip archive sample ]]
local unz = fs.unz.open(package.__dir .. "/iosample.zip")

assert(unz ~= nil)
assert(unz:locate_first())

print "✅ OK: fs.unz.archiver_t:open-info"
repeat
    local info = unz:info(true)
    printf("\t%s: %s\n", info.filename, info:getcontent():tostr())
until not unz:locate_next()
unz:close()

assert(fs.rmdir(package.__dir .. "/iosample"))
assert(fs.rmfile(package.__dir .. "/iosample.zip"))
assert(not fs.path.isdir(package.__dir .. "/iosample"))
assert(not fs.path.isfile(package.__dir .. "/iosample.zip"))
print "✅ OK: fs.rmdir, fs.rmfile"
