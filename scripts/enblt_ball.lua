RADIUS = 1
DAMAGE = 1
posx = 0
posy = 0

-- init(typename string, position x, position y, radius, damage, number of frames, animation delay)
function start(srcx, srcy, tgtx, tgty)
	posx = srcx-1
	posy = srcy-1
	init("ball", posx, posy, RADIUS, DAMAGE, 1, 0)
end

function update()
	posy -= 4
	updatePos(0, 10)
end