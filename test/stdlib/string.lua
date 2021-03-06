local base = require "./base" -- require */test/stdlib/base.lua

assert(base.filename:u8sub(-8) == "base.lua")
assert(base.directory:u8sub(-6) == "stdlib")
printf("✅ OK: required './base' module info:\n\tfilename: %s\n\tdirectory: %s\n", base.filename, base.directory)

local byte = ("あ"):u8byte(1)
assert(byte == 12354)
printf("✅ OK: utf8.byte(あ) = %d\n", byte)

local char = string.u8char(12355)
assert(char == "ぃ")
printf("✅ OK: utf8.char(12355) = %s\n", char)

local text = "❓ hello, 世界 ❗"
assert(text:u8len() == 13)
assert(text:len() == 21)
assert(Aula.Encoding.getEncodingName(text) == "UTF-8")
printf(
    "✅ OK: string.u8len, string.len\n\ttext: %s\n\tlength: %d\n\tbytes: %d\n\tencoding: %s\n",
    text,
    text:u8len(),
    text:len(),
    Aula.Encoding.getEncodingName(text)
)

local index1, index2, found = text:u8find("([a-zA-Z]+)")
assert(index1 == 3)
assert(index2 == 7)
assert(found == "hello")
printf("✅ OK: string.u8find\n\tstart: %d\n\tend: %d\n\tfound: %s\n", index1, index2, found)

local matched = text:u8match("[a-zA-Z]")
assert(matched == "h")
printf("✅ OK: string.u8match\n\ttext: %s\n\tregex: %s\n\tmatched: %s\n", text, "[a-zA-Z]", matched)

local alphabets, i = {"h", "e", "l", "l", "o"}, 1
for matched in text:u8gmatch("[a-zA-Z]") do
    assert(matched == alphabets[i])
    i = i + 1
end
printf("✅ OK: string.u8gmatch\n\ttext: %s\n\tregex: %s\n\tmatched: %s\n", text, "[a-zA-Z]", table.serialize(alphabets))

local changed = text:u8gsub("[a-zA-Z]+", "❇️")
assert(changed == "❓ ❇️, 世界 ❗")
printf("✅ OK: string.u8gsub: %s\n", changed)

local upper = text:u8upper()
assert(upper == "❓ HELLO, 世界 ❗")
printf("✅ OK: string.u8upper\n\ttext: %s\n", upper)

local lower = upper:u8lower()
assert(lower == "❓ hello, 世界 ❗")
printf("✅ OK: string.u8lower\n\ttext: %s\n", lower)

local rev = text:u8reverse()
assert(rev == "❗ 界世 ,olleh ❓")
printf("✅ OK: string.u8reverse\n\ttext: %s\n", rev)

local text2 = "❓ hELlO, 世界 ❗"
assert(text:same(text2, false))
printf("✅ OK: string.equal\n\ttext: %s\n\ttext2: %s\n", text, text2)
