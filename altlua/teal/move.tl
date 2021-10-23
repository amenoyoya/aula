local record Move
    vx: number
    vy: number
end

function Move.new(vx: number, vy: number): Move
    return setmetatable({vx = vx, vy = vy} as Move, { __index = Move })
end

return Move
