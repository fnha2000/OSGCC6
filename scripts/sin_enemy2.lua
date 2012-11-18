currentx = -5
currenty = -5
xspeed = -4
width = 5
height = 5

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start(srcx, srcy)
	currentx = srcx
	currenty = srcy
	init("normal", currentx, currenty, weight, height, 10, 1, 0)
end

function update()
	currentx += xspeed
	if currentx < -width || currentx > 800 then
		kill()
	else
		movey = math.sin(math.pi / 200 * currentx)
		movey = movey * 100 + 250 
		movey = movey - currenty
		currenty += movey
		updatePos(xspeed, move y)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)
	
	if currentx > 100 && currentx < 110 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
	if currentx > 300 && currentx < 310 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
	if currentx > 490 && currentx < 500 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
	if currentx > 690 && currentx < 700 then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
end