print("✅ Current directory:", __dir())
print("✅ Current file:", __file())

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
