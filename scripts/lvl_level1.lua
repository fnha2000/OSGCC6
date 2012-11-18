function start()
	setBGM("battleBGM.ogg")
	setBG("bg.png")
end

function update()
	if elapsedTime() == 120 then
		addEnemy("enem_sin1", -5, 10)
		addEnemy("enem_sin1", -5, 15)
		addEnemy("enem_sin1", -5, 20)
	end
	if elapsedTime() == 1800 then
		addEnemy("enem_special", 400, -10)
	end
	if elapsedTime() == 3600 then
		addEnemy("enem_boss1", 300, -100)
	end
end

