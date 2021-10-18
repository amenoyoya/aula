-- stdin: readln = Aula.IO.Stdin:readString
local stdin = readln "Press 'y' > "
assert(stdin == "y")
printf("\t⭕ Your input is '%s' => OK\n", stdin)
