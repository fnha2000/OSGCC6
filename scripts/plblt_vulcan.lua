WIDTH = 5
HEIGHT = 5
DAMAGE = 1
posx = 0
posy = 0

function start(srcx, srcy, tgtx, tgty)
	posx = srcx-2.5
	posy = srcy-2.5
	init("vulcan", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	posy -= 10
	updatePos(0, 10)
end