WIDTH = 5
HEIGHT = 10
DAMAGE = 2
posx = 0
posy = 0

function start(srcx, srcy, tgtx, tgty)
	posx = srcx-2.5
	posy = srcy-5
	init("laser", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	posy = posy - 10
	updatePos(0, 10)
end