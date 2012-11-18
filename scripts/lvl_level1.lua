counter = 0
boss = 0

function start()
	setBGM("battleBGM.ogg")
	setBG("bg.png")
end

function update()
	if elapsedTime() < 1200 then
		if counter < 240 then enemypattern1() end
	elseif elapsedTime() < 2400 then
		if counter < 240 then enemypattern2() end
	elseif elapsedTime() < 3600 then
		if counter < 240 then enemypattern3() end
	else
		if boss == 0 then
			addEnemy("enem_boss1", 300, -150)
			boss = 1
		end	
	end
	
	if (elapsedTime() % 600) == 0 then
		addEnemy("enem_special", 400, -10)
	end
	
	counter = counter + 1
	if counter > 300 then counter = 1 end
end

function enemyPattern1()
	if (elapsedTime() % 20) == 0 then
		addEnemy("enem_hori1", -10, 100)
		addEnemy("enem_hori2", 800, 100)
	end
	if (elapsedTime() % 40) == 0 then
		addEnemy("enem_hori1", -10, 150)
		addEnemy("enem_hori2", 800, 100)
	end
	if (elapsedTime() % 60) == 0 then
		addEnemy("enem_hori1", -10, 200)
		addEnemy("enem_hori2", 800, 100)
	end
end

function enemyPattern3()
	if (elapsedTime() % 20) == 0 then
		addEnemy("enem_sine1", -10, 100)
		addEnemy("enem_sine2", 800, 100)
		addEnemy("enem_hori1", -10, 0)
		addEnemy("enem_hori1", -10, 20)
		addEnemy("enem_hori1", -10, 40)
	end
	if (elapsedTime() % 40) == 0 then
		addEnemy("enem_sine1", -10, 150)
		addEnemy("enem_sine2", 800, 100)
		addEnemy("enem_hori1", 800, 0)
		addEnemy("enem_hori1", 800, 20)
		addEnemy("enem_hori1", 800, 40)
	end
	if (elapsedTime() % 60) == 0 then
		addEnemy("enem_sine1", -10, 200)
		addEnemy("enem_sine2", 800, 100)
		addEnemy("enem_ellipse1", 100, 0)
		addEnemy("enem_ellopse1", 300, 0)
		addEnemy("enem_ellipse1", 500, 0)
	end
end

function enemyPattern2()
	if (elapsedTime() % 20) == 0 then
		addEnemy("enem_cos1", -10, 100)
		addEnemy("enem_cos2", 800, 100)
		addEnemy("enem_hori1", -10, 0)
	end
	if (elapsedTime() % 40) == 0 then
		addEnemy("enem_cos1", -10, 150)
		addEnemy("enem_cos2", 800, 100)
		addEnemy("enem_hori1", 800, 0)
	end
	if (elapsedTime() % 60) == 0 then
		addEnemy("enem_cos1", -10, 200)
		addEnemy("enem_cos2", 800, 100)
	end
end

