WIDTH = 10
HEIGHT = 17
DAMAGE = 1
posx = 0
posy = 0

function start(srcx, srcy, tgtx, tgty)
	posx = srcx-5
	posy = srcy-8.5
	init("vulcan", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	posy = posy + 10
	updatePos(0, 10)
end