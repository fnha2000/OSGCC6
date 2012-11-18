IDLEPOSX = 550
HLPOSX = 580
POSY = 420
POSITION = 1
currentx = IDLEPOSX

function start()
	Init("help", 550, POSY, 200, 60, 1, 0, POSITION)
end

function update()
	if getMenuChoice() == POSITION then
		if currentx < HLPOSX then
			currentx = currentx + 2
		end
	else
		if currentx > IDLEPOSX then
			currentx = currentx - 2
		end
	end
	updatePos(currentx, POSY)
end

