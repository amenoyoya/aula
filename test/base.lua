-- UTF-8 stdout print
print "✅ OK: print(UTF-8) ⭕"

-- UTF-8 stdout printf
assert(("✅"):u8byte(1) == 9989)
printf("%s %s: printf(UTF-%d, string, string, number)\n", string.u8char(9989), "OK", 8)
