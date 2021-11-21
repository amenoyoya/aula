assert(fs.path.basename(package.__dir) == "test")
print("✅ Current directory:", package.__dir)

assert(fs.path.basename(package.__file) == "api_test.lua")
print("✅ Current file:", package.__file)

assert(fs.path.stem(os.argv[0]) == "aula")
assert(os.argv[1] == "test")
print("✅ os.argv", os.argv)

print("\n⭐ Test for stdin/stdout")
require "./base" -- module name has "/" => relative require: require {__dir}/base.lua

print("\n⭐ Test for string library")
require "stdlib/string" -- require {__dir}/stdlib/string.lua

print("\n⭐ Test for filesystem library")
require "stdlib/fs" -- require {__dir}/stdlib/fs/init.lua

print("\n⭐ Test for table library")
require "stdlib/table" -- require {__dir}/stdlib/table.lua

print("\n⭐ Test for package library")
require "stdlib/package" -- require {__dir}/stdlib/package.lua
