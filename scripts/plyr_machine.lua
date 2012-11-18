WIDTH = 50
HEIGHT = 50
RADIUS = 2
SPEED = 10
FOCUSSPEED = 5
MHEALTH = 1
powerlevel = 1
weaponlevel = 1
weapontype[1] = "vulcan"
weapontype[2] = "laser"
frontdelay[1] = 5
frontdelay[2] = 2
sidedelay = 900
backdelay = 600
frontcooldown = 0
sidecooldown = 0
backcooldown = 0

function start()
	init("machine", RADIUS, 375, 500, WIDTH, HEIGHT, MHEALTH, SPEED, FOCUSSPEED, 1, 0)
end

function update()
	front, back, side = isFiring()
	curx, cury = currentPos()
	if front == 1 then
		if frontcooldown == frontdelay[weaponlevel] then
			frontcooldown = 0
			if powerlevel == 1 then
				addBullet(weapontype[weaponlevel], curx+25, cury-5, -1, -1)
			else if powerlevel == 2 then
				addBullet(weapontype[weaponlevel], curx+10, cury-5, -1, -1)
				addBullet(weapontype[weaponlevel], curx+30, cury-5, -1, -1)
			else
				addBullet(weapontype[weaponlevel], curx+10, cury-5, -1, -1)
				addBullet(weapontype[weaponlevel], curx+25, cury-5, -1, -1)
				addBullet(weapontype[weaponlevel], curx+40, cury-5, -1, -1)
			end
		else
			frontcooldown = frontcooldown + 1
		end
		framesPast = 0
	end
	if back == 1 then
		if backcooldown == backdelay then
			backcooldown = 0
			addBullet("shotgun", curx+25, cury+25, curx+25, cury+30)
			addBullet("shotgun", curx+25, cury+25, curx+20, cury+30)
			addBullet("shotgun", curx+25, cury+25, curx+30, cury+30)
			addBullet("shotgun", curx+25, cury+25, curx+15, cury+30)
			addBullet("shotgun", curx+25, cury+25, curx+35, cury+30)
			addBullet("shotgun", curx+25, cury+25, curx+25, cury+30)
		else
			backcooldown = backcooldown + 1
		end
	end
	if side == 1 then
		if sidecooldown == sidedelay then
			sidecooldown = 0
			addBullet("shockwave", curx, cury, curx-25, cury)
			addBullet("shockwave", curx+WIDTH, cury, curx+WIDTH+25, cury)
		else
			sidecooldown = sidecooldown + 1
		end
	end
end

function powerup()
	if powerlevel < 3 then
		powerlevel = powerlevel + 1
	else
		if weaponlevel == 1 then
			weaponlevel = 2
			powerlevel = 1
		end
	end
end