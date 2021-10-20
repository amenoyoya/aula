local function add(a: number, b: number): number
    return a + b
end

local s: number = add(1, 2)
assert(s == 3)
printf("✅ teal script: add(1, 2) => %d\n", s)
