#! /usr/bin/env lua5.3

function table.slice(self, from, to)
    local new = {}
    from = from or 1
    to = to or #self
    for i = 1, to - from + 1 do
        new[i] = self[i + from - 1]
    end
    return new
end

arg = table.slice(os.argv, 2)
table.insert( arg, 1, "" )
require( 'lune.base.base' )

