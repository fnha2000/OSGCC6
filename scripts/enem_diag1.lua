currentx = -5
currenty = -5
xspeed = 4
yspeed = 2
width = 5
height = 5

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start(srcx, srcy)
	currentx = srcx
	currenty = srcy
	init("diag1", currentx, currenty, width, height, 10, 1, 0)
end

function update()
	currentx = currentx + xspeed
	currenty = currentx + yspeed
	if currentx > 800 || currenty > 600 then
		kill()
	else
		updatePos(xspeed, yspeed)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)

	if currentx > 150 and currentx < 160 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 350 and currentx < 360 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 550 and currentx < 560 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
end