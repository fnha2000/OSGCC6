currentx = -5
currenty = -5
xspeed = 3
yspeed = 3
width = 5
height = 5

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start()
	init("normal", -5, -5, 10, 10, 10, 1, 0)
end

function update()
	if timePassed() < 3000 then
		currentx += xspeed
		currenty += yspeed
		updatePos(xspeed, yspeed)
	end
	if timePassed() > 3000 and timePassed() < 6000 then
		currentx -= xpseed
		currenty -= yspeed
		updatePos(-xspeed, -yspeed)
	end
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)
	addBullet("ball", 0, currentx + 2.5, currenty + 2.5)
end