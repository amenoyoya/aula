assert(Aula.Path.getBaseName(package.__dir) == "test")
print("✅ Current directory:", package.__dir)

assert(Aula.Path.getBaseName(package.__chunk) == "api_test.lua")
print("✅ Current file:", package.__chunk)

assert(Aula.Path.getBaseStem(os.argv[0]) == "aula")
assert(os.argv[1] == "test")
print("✅ os.argv", os.argv)

print("\n⭐ Test for stdin/stdout")
require(package.__dir .. "/base")

print("\n⭐ Test for string library")
require "stdlib/string" -- require {__dir}/stdlib/string.lua

print("\n⭐ Test for io library")
require "stdlib/io" -- require {__dir}/stdlib/io/init.lua

print("\n⭐ Test for table library")
require "stdlib/table" -- require {__dir}/stdlib/table.lua

print("\n⭐ Test for package library")
require "stdlib/package" -- require {__dir}/stdlib/package.lua
