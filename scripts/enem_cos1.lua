currentx = -5
currenty = -5
xspeed = 4
width = 5
height = 5

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start(srcx, srcy)
	currentx = srcx
	currenty = srcy
	init("cos1", currentx, currenty, width, height, 10, 1, 0)
end

function update()
	currentx = currentx + xspeed
	if currentx > 800 then
		kill()
	else
		movey = math.cos(math.pi / 200 * currentx)
		movey = movey * 100 + 250 
		movey = movey - currenty
		currenty = currenty + movey
		updatePos(xspeed, move y)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)
	
	if currentx > 100 and currentx < 110 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 300 and currentx < 310 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 490 and currentx < 500 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
	if currentx > 690 and currentx < 700 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2, currentx + width/2, currenty + height)
	end
end