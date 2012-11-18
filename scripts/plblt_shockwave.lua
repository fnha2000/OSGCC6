WIDTH = 10
HEIGHT = 50
DAMAGE = 30
SPEED = 10
posx = 0
posy = 0
direction = 0
framespast = 0

function start(srcx, srcy, tgtx, tgty)
	posx = srcx-5
	posy = srcy-25
	direction = tgtx - srcx
	init("shotgun", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	framespast = framespast + 1
	if framespast >= 15 then kill()
	else
		if direction < 0 then
			posx = posx - SPEED
			updatePos(-SPEED, 0)
		else
			posx = posx + SPEED
			updatePos(SPEED, 0)
		end
	end
end