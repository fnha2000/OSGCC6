RADIUS = 1
DAMAGE = 1
posx = 0
posy = 0
SPEED = 8
speedx = 0
speedy = -4

-- init(typename string, position x, position y, radius, damage, number of frames, animation delay)
function start(srcx, srcy, tgtx, tgty)
	length = math.sqrt((tgtx-srcx)^2 + (tgty-srcy)^2)
	if tgtx < 0 and tgty < 0 then
		--calculate unit vector * speed
		speedx = (tgtx - srcx)/length * SPEED
		speedy = (tgty - srcy)/length * SPEED
	end
	posx = srcx-1
	posy = srcy-1
	init("ball", posx, posy, RADIUS, DAMAGE, 1, 0)
end

function update()
	posx = posx + speedx
	posy = posy + speedy
	updatePos(speedx, speedy)
end