local record Point
    x: number
    y: number
end

function Point.new(x: number, y: number): Point
    return setmetatable({x = x, y = y} as Point, { __index = Point })
end

return Point
