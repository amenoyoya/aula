-- UTF-8 stdout print
print "✅ OK: print(UTF-8) ⭕"

-- UTF-8 stdout printf
assert(("✅"):u8byte(1) == 9989)
printf("%s %s: printf(UTF-%d, string, string, number)\n", string.u8char(9989), "OK", 8)

-- stdin: readln = Aula.IO.Stdin:readString
local stdin = readln "✅ OK: readln = Aula.IO.Stdin:readString\nPress 'y' to continue testing > "
if stdin == "y" then
    printf("\t⭕ Your input is '%s' => continue...\n", stdin)
else
    printf("\t❌ Your input is '%s' => exit...\n", stdin)
    os.exit()
end
