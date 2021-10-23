local Character = require "character"
local Move = require "move"

-- following code is error: beacause Character.hello method not declared
function Character:hello()
    print("Hello")
end

local ch: Character = Character.new()

ch:walk(Move.new(10, -10))
print(ch:where())
print(2 | 4)

-- following code is error
ch:hello() -- invalid method
ch:walk({10, -10}) -- argument type mismatch
