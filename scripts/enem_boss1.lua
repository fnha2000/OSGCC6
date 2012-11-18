currentx = -5
currenty = -5
xspeed = 3
yspeed = 0.5
width = 200
height = 150
health = 1000
state = 1
counter = 1

-- init(typename string, position x, position y, width, height, maxhealth, number of frames, animation delay)
function start(srcx, srcy)
	currentx = srcx
	currenty = srcy
	init("boss1", currentx, currenty, width, height, health, 1, 0)
end

function update()
	if state == 1 then
		currenty = currenty + yspeed
		updatePos(0, yspeed)
		if(currenty > 100) then
			state = 2
			clearBullets()
		else
			bulletPattern1()
		end
	else
		currentx = currentx + xspeed
		bound = 800 - width
		if currentx > bound then
			move = xspeed - currentx + bound
			currentx = bound
			xspeed = xspeed * -1
			updatePos(move, 0)
		elseif currentx < 0 then
			move = xspeed + currentx
			currentx = 0
			xspeed = xspeed * -1
			updatePos(move, 0)		
		else
			updatePos(xspeed, 0)
		end
				
		if state == 2 then
			if getHealth() < 750 then
				state == 3
				clearBullets()
			else
				bulletPattern2()
			end
		elseif state == 3 then
			if getHealth() < 500 then
				state = 4
				clearBullets()
			else
				bulletPattern3()
			end
		elseif state == 4 then
			if getHealth() < 250 then
				state += 5
				clearBullets()
			else
				bulletPattern4()
			end
		else
				bulletPattern5()
		end
	end
	
	counter = counter + 1
	if counter > 300 then conuter = 1 end
	
	-- addBullet(typename string, will target player(0 or 1), source position x, source position y)
end

function bulletPattern1()
	if counter <= 120 then
		if (counter % 20) == 0 then 
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx, currenty)
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx + 100, currenty)
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx, currenty + 100)
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx + 100, currenty + 100)
			
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 100, currenty)
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 200, currenty)
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 100, currenty + 100)
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 200, currenty + 100)
			
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx, currenty + 100)
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx + 100, currenty + 100)
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx, currenty + 200)
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx + 100, currenty + 200)
			
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 100, currenty + 100)
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 200, currenty + 100)
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 100, currenty + 200)
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 200, currenty + 200)
		end
	end
	if counter > 120 && counter <= 240
		if (counter % 20) == 0 then 
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx, currenty + 50)
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx + 100, currenty + 50)
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx + 50, currenty)
			addBullet("ball", 0, currentx + 50, currenty + 50, currentx + 50, currenty + 100)
			
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx, currenty + 50)
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 200, currenty + 50)
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 150, currenty)
			addBullet("ball", 0, currentx + 150, currenty + 50, currentx + 150, currenty + 100)
			
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx, currenty + 150)
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx + 100, currenty + 150)
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx + 50, currenty)
			addBullet("ball", 0, currentx + 50, currenty + 150, currentx + 50, currenty + 200)
			
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx, currenty + 150)
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 200, currenty + 150)
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 150, currenty)
			addBullet("ball", 0, currentx + 150, currenty + 150, currentx + 150, currenty + 200)
		end
	end
end

function bulletPattern3()
	if counter <= 240 then
		addBullet("ball", 0, currentx + width, currenty + height/2, currentx + width, currenty + height)
		addBullet("ball", 0, currentx + 50, currenty + height/2, currentx + 50, currenty + height)
		addBullet("ball", 0, currentx + 150, currenty + height/2, currentx + 150, currenty + height)
	end	
end

function bulletPattern3()
	if counter <= 240 then
		if (counter % 20) == 0 then 
			addBullet("ball", 1, currentx, currenty + 50, currentx, currenty)
			addBullet("ball", 1, currentx + 50, currenty + 50, currentx, currenty)
			addBullet("ball", 1, currentx + 100, currenty + 50, currentx, currenty)
			addBullet("ball", 1, currentx + 150, currenty + 50, currentx, currenty)
			addBullet("ball", 1, currentx + 200, currenty + 50, currentx, currenty)
			addBullet("ball", 1, currentx, currenty + 150, currentx, currenty)
			addBullet("ball", 1, currentx + 50, currenty + 150, currentx, currenty)
			addBullet("ball", 1, currentx + 100, currenty + 150, currentx, currenty)
			addBullet("ball", 1, currentx + 150, currenty + 150, currentx, currenty)
			addBullet("ball", 1, currentx + 200, currenty + 150, currentx, currenty)
		end
	end	
end

function bulletPattern4()
	bulletPattern1()
	bulletPattern2()
end

function bulletPattern5()
	bulletPattern3()
	bulletPattern2()
end
