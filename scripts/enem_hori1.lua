currentx = -5
currenty = -5
xspeed = 3
width = 5
height = 5

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start(srcx, srcy)
	currentx = srcx
	currenty = srcy
	init("hori1", currentx, currenty, width, height, 10, 1, 0)
end

function update()
	currentx = currentx + xspeed
	bound = 800 - width
	if currentx > bound then
		move = xspeed - currentx + bound
		currentx = bound
		xspeed = xspeed * -1
		updatePos(move, 0)
	elseif currentx < -width && xspeed < 0 then
		kill()
	else
		updatePos(xspeed, 0)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)

	if currentx > 200 and currentx < 210 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 400 and currentx < 410 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 600 and currentx < 610 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
end