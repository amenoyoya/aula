local function add(a: number, b: number): number
    return a + b
end

-- to use unknown function, you must declare the interface
global printf: function(string, ...: any)

local s: number = add(1, 2)
assert(s == 3)
printf("✅ teal script: add(1, 2) => %d\n", s)

-- teal can bit operations
local i = 2 | 4 -- bit32.bor(2, 4)
assert(i == 6)
printf("✅ bit operation: 2 | 4 => %d\n", i)
