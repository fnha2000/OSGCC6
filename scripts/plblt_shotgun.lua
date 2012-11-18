WIDTH = 20
HEIGHT = 20
DAMAGE = 10
SPEED = 15
posx = 0
posy = 0
speedx = 0
speedy = 0
framespast = 0

function start(srcx, srcy, tgtx, tgty)
	length = math.sqrt((tgtx-srcx)^2 + (tgty-srcy)^2)
	posx = srcx-10
	posy = srcy-10
	speedx = (tgtx - srcx)/length * SPEED
	speedy = (tgty - srcy)/length * SPEED
	init("shotgun", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	framespast = framespast + 1
	if framespast >= 15 then kill()
	else
		posx = posx + speedx
		posy = posy + speedy
		updatePos(speedx, speedy)
	end
end