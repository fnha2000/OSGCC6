#include "Enemy.h"

enem_init_Vals enemInitVals;
enem_position enemPos;
enem_newBullet enemNewBlt;
float toSendHealth;
bool clearBullets = false;
bool killEnemy = false;

void enem_load(Enemy *enemy, std::string type, float srcx, float srcy) {
	enemNewBlt.exists = false;
	std::string filename = "enem_" + type + ".lua";
	loadScript(&enemy->script, filename);
	regFunction(&enemy->script, "init", enem_init);
	regFunction(&enemy->script, "updatePos", enem_getPos);
	regFunction(&enemy->script, "addBullet", enem_recvBullet);
	regFunction(&enemy->script, "clearBullets", enem_removeBlts);
	regFunction(&enemy->script, "kill", enem_kill);
	regFunction(&enemy->script, "timePassed", timePassed);
	regFunction(&enemy->script, "win", winLevel);
	regFunction(&enemy->script, "curHealth", enem_sendHealth);
	runFunction(&enemy->script, "start", srcx, srcy);
	enem_loadValues(enemy);
}

int enem_init(lua_State *L) {
	enemInitVals.type = lua_tostring(L, 1);
	enemInitVals.px = lua_tonumber(L, 2);
	enemInitVals.py = lua_tonumber(L, 3);
	enemInitVals.width = lua_tonumber(L, 4);
	enemInitVals.height = lua_tonumber(L, 5);
	enemInitVals.maxhealth = lua_tonumber(L, 6);
	enemInitVals.frames = lua_tointeger(L, 7);
	enemInitVals.animdelay = lua_tointeger(L, 8);
	lua_pop(L, 8);
	return 0;
}

void enem_loadValues(Enemy *enemy) {
	enemy->type = enemInitVals.type;
	enemy->x = enemInitVals.px;
	enemy->y = enemInitVals.py;
	enemy->width = enemInitVals.width;
	enemy->height = enemInitVals.height;
	enemy->health = enemy->maxhealth = enemInitVals.maxhealth;
	enemy->frames = enemInitVals.frames;
	enemy->curframe = 0;
	enemy->animdelay = enemInitVals.animdelay;
	enemy->animframespast = 0;
	enemy->dead = false;
	rect_init(&enemy->hitbox, enemy->x, enemy->y, enemy->width, enemy->height);
	enemy->images = (ALLEGRO_BITMAP **)malloc(enemInitVals.frames * sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < enemy->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "enemy/" + enemInitVals.type + "/" + out.str() + ".png";
		enemy->images[i] = dx_getGame()->resources.get_image(filename);
	}
}

bool enem_hit(Enemy *enemy, PlayerBullet *p) {
	if (!enemy->dead) {
		if (rect_intersects(&enemy->hitbox, &p->hitbox)) return true;
	}
	return false;
}

int enem_recvBullet(lua_State *L) {
	enemNewBlt.exists = true;
	enemNewBlt.type = lua_tostring(L, 1);
	enemNewBlt.targeted = lua_tointeger(L, 2);
	enemNewBlt.srcx = lua_tonumber(L, 3);
	enemNewBlt.srcy = lua_tonumber(L, 4);
	enemNewBlt.tgtx = lua_tonumber(L, 5);
	enemNewBlt.tgty = lua_tonumber(L, 6);
	lua_pop(L, 6);
	return 0;
}

void enem_addBullet(Enemy *enemy) {
	EnemyBullet newBullet;
	if (enemNewBlt.targeted == 0) {
		enblt_load(&newBullet, enemNewBlt.type, enemNewBlt.srcx, enemNewBlt.srcy, -1, -1);
		if (enemNewBlt.tgtx > 0 && enemNewBlt.tgty > 0) {
			enblt_load(&newBullet, enemNewBlt.type, enemNewBlt.srcx, enemNewBlt.srcy, enemNewBlt.tgtx, enemNewBlt.tgty);
		}
	}
	else {
		float tgtx = dx_getGame()->player->x;
		float tgty = dx_getGame()->player->y;
		enblt_load(&newBullet, enemNewBlt.type, enemNewBlt.srcx, enemNewBlt.srcy, tgtx, tgty);
	}
	enemy->bullets.push_back(newBullet);
	enemNewBlt.exists = false;
}

void enem_clearBullets(Enemy *enemy) {
	enemy->bullets.clear();
}

int enem_getPos(lua_State *L) {
	enemPos.x += lua_tonumber(L, 1);
	enemPos.y += lua_tonumber(L, 2);
	lua_pop(L, 2);
	return 0;
}

int enem_sendHealth(lua_State *L) {
	lua_pushnumber(L, toSendHealth);
	return 1;
}

int enem_removeBlts(lua_State *L) {
	clearBullets = true;
	return 0;
}

int enem_kill(lua_State *L) {
	killEnemy = true;
	return 0;
}

int enem_spawnItem(lua_State *L) {
	std::string type = lua_tostring(L, 1);
	lua_pop(L, 1);
	addItem(type);
	return 0;
}

void enem_loadPos(Enemy *enemy) {
	enemy->x += enemPos.x;
	enemy->y += enemPos.y;
	rect_translate(&enemy->hitbox, enemPos.x, enemPos.y);
}

void enem_update(Enemy *enemy) {
	toSendHealth = enemy->health;
	runFunction(&enemy->script, "update");
	if (killEnemy) {
		enemy->dead = true;
		killEnemy = false;
	}
	else enem_loadPos(enemy);
	if (enemNewBlt.exists) enem_addBullet(enemy);
	if (clearBullets) {
		clearBullets = false;
		enemy->bullets.clear();
	}
	enem_animate(enemy);
}

void enem_animate(Enemy *enemy) {
	if (enemy->frames > 1) {
		enemy->animframespast++;
		if (enemy->animframespast == enemy->animdelay) {
			enemy->animframespast = 0;
			enemy->curframe = (enemy->curframe + 1) % enemy->frames;
		}
	}
}

void enem_close(Enemy *enemy) {
	closeScript(&enemy->script);
	free(enemy->images);
}