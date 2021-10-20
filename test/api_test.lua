assert(Aula.Path.getBaseName(__dir()) == "test")
print("✅ Current directory:", __dir())

assert(Aula.Path.getBaseName(__file()) == "api_test.lua")
print("✅ Current file:", __file())

assert(Aula.Path.getBaseStem(os.argv[0]) == "aula")
assert(os.argv[1] == "test")
print("✅ os.argv", os.argv)

print("\n⭐ Test for stdin/stdout")
include "base" -- require {__dir}/base.lua

print("\n⭐ Test for string library")
include "stdlib/string" -- require {__dir}/stdlib/string.lua

print("\n⭐ Test for io library")
include "stdlib/io" -- require {__dir}/stdlib/io/main.lua

print("\n⭐ Test for table library")
include "stdlib/table" -- require {__dir}/stdlib/table.lua

print("\n⭐ Test for package library")
include "stdlib/package" -- require {__dir}/stdlib/package.lua
