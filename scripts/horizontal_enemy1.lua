currentx = -5
currenty = -5
xspeed = 3
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
	bound = 800 - width
	if currentx > bound then
		move = xspeed - currentx + bound
		currentx = bound
		xspeed *= -1
		updatePos(move, 0)
	elseif currentx < -width && xspeed < 0 then
		kill()
	else
		updatePos(xspeed, 0)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)
	
	if currentx > 0 && ((currentx % 200) == 0) then
		addBullet("ball", 0, currentx + width/2, currenty + height/2)
	end
end