WIDTH = 2
HEIGHT = 10
DAMAGE = 30
SPEED = 10
posx = 0
posy = 0
direction = 0
framespast = 0

function start(srcx, srcy, tgtx, tgty)
	posx = srcx-1
	posy = srcy-5
	direction = tgtx - srcx
	init("shotgun", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	framespast += 1
	if framespast >= 15 then kill()
	else
		if direction < 0 then
			posx -= SPEED
			updatePos(-SPEED, 0)
		else
			posx += SPEED
			updatePos(SPEED, 0)
		end
	end
end