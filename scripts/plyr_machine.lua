powerlevel = 1
weaponlevel = 1
firedelay1 = 5
firedelay2 = 2
framesPast = 0

function start(srcx, srcy, tgtx, tgty)
	init("machine", posx, posy, WIDTH, HEIGHT, DAMAGE, 1, 0)
end

function update()
	if isFiring() == 1 then
		
		framesPast = 0
	else
	
	end
end