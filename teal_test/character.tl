local Point = require 'point'
local Move = require 'move'

local record Character
    position: Point
    walk: function(Character, Move): Point
    where: function(Character): Point
end

function Character.new(): Character
    return setmetatable({position = Point.new(0, 0)} as Character, { __index = Character })
end

function Character:walk(move: Move): Point
    self.position.x = self.position.x + move.vx
    self.position.y = self.position.y + move.vy
    return self.position
end

function Character:where(): Point
    return self.position
end

return Character
