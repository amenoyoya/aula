--- Core library ---

-- @private Check type is same
-- @param {string} typename
-- @param {string} types: If you want to check for multiple types, designate like following: "string|number|boolean"
--                        If you want to skip the check, designate "any"
local function typesame(typename, types)
    for t in types:gmatch"[^|]+" do
        if t == "any" or typename == t then return true end
    end
    return false
end

-- Type checker for function arguments
-- @param {number} n: argument count
function debug.checkarg(n, ...)
    local funcname = debug.getinfo(2, "n").name
    local args = {...}
    -- ipairs can't scan all elements if the list is like {1, nil, 3} (scan only 1)
    for i = 1, n * 2 - 1, 2 do
        local t = type(args[i])
        if not typesame(t, args[i + 1]) then
            error(string.format(
                "function argument type error: '%s' argument %d expected %s, but got %s",
                funcname,
                math.floor((i - 1) / 2) + 1,
                args[i + 1],
                t
            ))
        end
    end
end

-- Flag for serialization when printing table
table.print_flag = true -- true: print(tbl) => table.serialize(tbl, 2, true)

-- @private General print function
-- * support UTF-8 for Windows
-- * support to print nil
local function fprint(printfunc, ...)
    local list = {...} -- #list returns 1 if the list is like {1, nil, 3}
    local key = 0
    -- ipairs can't scan all elements if the list is like {1, nil, 3} (scan only 1)
    for k, v in pairs(list) do
        if key > 0 then printfunc "\t" end
        if k > key + 1 then
            for i = 1, k - key - 1 do
                printfunc "nil\t"
            end
        end
        printfunc((type(list[k]) == 'table' and table.print_flag) and table.serialize(list[k], 2, true) or tostring(list[k]))
        key = k
    end
    printfunc((key == 0 and "nil" or "") .. "\n")
end

-- Override default `print` function
function print(...)
    fprint(io.print, ...)
end

-- Print formatted string
function printf(format, ...)
    io.print(format:format(...))
end

-- Error print function
function eprint(...)
    fprint(io.eprint, ...)
end

function eprintf(format, ...)
    io.eprint(format:format())
end

-- Print formatted string to stderr
function errorf(format, ...)
    return error(format:format(...))
end

-- Read string from stdin (support UTF-8 for Windows)
function readln(message, size)
    if type(message) == 'string' then
        io.print(message)
    end
    return io.getstr(size or 1024)
end
