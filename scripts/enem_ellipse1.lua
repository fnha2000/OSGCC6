currentx = -5
currenty = -5
xspeed = 4
width = 5
height = 5
centerx = 0

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start(srcx, srcy)
	currentx = srcx
	currenty = srcy
	centerx = srcx + 100
	init("ellipse1", currentx, currenty, width, height, 10, 1, 0)
end

function update()
	currentx += xspeed
	if currentx > (center + 100) then
		kill()
	else
		movey = math.sqrt(40000*(10000 - (currentx - centerx)*(currentx - centerx))/10000)
		movey = movey - currenty
		currenty += movey
		updatePos(xspeed, move y)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)
	
	if currentx > (center - 80) && currentx < (center - 70) then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
	if currentx > (center - 5) && currentx < (center + 5) then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
	if currentx > (center + 70) && currentx < (center + 80) then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
end