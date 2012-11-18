#include "Player.h"

plyr_init_Vals plyrInitVals;

void plyr_load(Player *player, std::string type) {
	std::string filename = "plyr_" + type + ".lua";
	loadScript(&player->script, filename);
	regFunction(&player->script, "init", plyr_init);
	regFunction(&player->script, "isFiring", plyr_isFiring);
	regFunction(&player->script, "addBullet", plyr_addBullet);
	regFunction(&player->script, "currentPos", plyr_sendPos);
	runFunction(&player->script, "start");
	plyr_loadValues(player);
	player->fireFront = player->fireBack = player->fireSide = 0;
}

int plyr_init(lua_State *L) {
	plyrInitVals.type = lua_tostring(L, 1);
	plyrInitVals.rad = lua_tonumber(L, 2);
	plyrInitVals.px = lua_tonumber(L, 3);
	plyrInitVals.py = lua_tonumber(L, 4);
	plyrInitVals.width = lua_tonumber(L, 5);
	plyrInitVals.height = lua_tonumber(L, 6);
	plyrInitVals.mhlth = lua_tonumber(L, 7);
	plyrInitVals.speed = lua_tonumber(L, 8);
	plyrInitVals.focusspeed = lua_tonumber(L, 9);
	plyrInitVals.frames = lua_tointeger(L, 10);
	plyrInitVals.animdelay = lua_tointeger(L, 11);
	lua_pop(L, 11);
	return 0;
}

void plyr_loadValues(Player *player) {
	player->curframe = 0;
	player->animframespast = 0;
	player->dead = player->movel = player->mover = player->moveu = player->moved = player->shielded = player->focused = false;
	player->canFire = true;
	player->frames = plyrInitVals.frames;
	player->animdelay = plyrInitVals.animdelay;
	player->images = (ALLEGRO_BITMAP **)malloc(plyrInitVals.frames * sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < player->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "player/" + plyrInitVals.type + "/" + out.str() + ".png";
		player->images[i] = dx_getGame()->resources.get_image(filename);
	}
	player->x = plyrInitVals.px;
	player->y = plyrInitVals.py;
	player->radius = plyrInitVals.rad;
	player->width = plyrInitVals.width;
	player->height = plyrInitVals.height;
	player->health = player->maxhealth = plyrInitVals.mhlth;
	player->speed = plyrInitVals.speed;
	player->focusspeed = plyrInitVals.focusspeed;
	circ_init(&player->hitbox, (player->x + (player->width/2)), (player->y + (player->height/2)), player->radius);
	rect_init(&player->pickupbox, player->x, player->y, player->width, player->height);
}

bool plyr_hit(Player *player, EnemyBullet *p) {
	if (!player->dead) {
		if (circ_intersects(&player->hitbox, &p->hitbox)) return true;
	}
	return false;
}

int plyr_addBullet(lua_State *L) {
	std::string type = lua_tostring(L, 1);
	float srcx = lua_tonumber(L, 2);
	float srcy = lua_tonumber(L, 3);
	float tgtx = lua_tonumber(L, 4);
	float tgty = lua_tonumber(L, 5);
	lua_pop(L, 5);
	PlayerBullet newblt;
	plblt_load(&newblt, type, srcx, srcy, tgtx, tgty);
	dx_getGame()->playerbullets.push_back(newblt);
	return 0;
}

int plyr_isFiring(lua_State *L) {
	lua_pushinteger(L, dx_getGame()->player->fireFront);
	lua_pushinteger(L, dx_getGame()->player->fireBack);
	lua_pushinteger(L, dx_getGame()->player->fireSide);
	return 3;
}

int plyr_sendPos(lua_State *L) {
	lua_pushnumber(L, dx_getGame()->player->x);
	lua_pushnumber(L, dx_getGame()->player->y);
	return 2;
}

void plyr_update(Player *player) {
	runFunction(&player->script, "update");
	if (player->movel) {
		if (player->focused) {
			player->x -= player->focusspeed;
			circ_translate(&player->hitbox, -player->focusspeed, 0);
			rect_translate(&player->pickupbox, -player->focusspeed, 0);
		}
		else {
			player->x -= player->speed;
			circ_translate(&player->hitbox, -player->speed, 0);
			rect_translate(&player->pickupbox, -player->speed, 0);
		}
	}
	if (player->mover) {
		if (player->focused) {
			player->x += player->focusspeed;
			circ_translate(&player->hitbox, -player->focusspeed, 0);
			rect_translate(&player->pickupbox, player->focusspeed, 0);
		}
		else {
			player->x += player->speed;
			circ_translate(&player->hitbox, player->speed, 0);
			rect_translate(&player->pickupbox, player->speed, 0);
		}
	}
	if (player->moveu) {
		if (player->focused) {
			player->y -= player->focusspeed;
			circ_translate(&player->hitbox, 0, -player->focusspeed);
			rect_translate(&player->pickupbox, 0, -player->focusspeed);
		}
		else {
			player->y -= player->speed;
			circ_translate(&player->hitbox, 0, -player->speed);
			rect_translate(&player->pickupbox, 0, -player->speed);
		}
	}
	if (player->moved) {
		if (player->focused) {
			player->y += player->focusspeed;
			circ_translate(&player->hitbox, 0, player->focusspeed);
			rect_translate(&player->pickupbox, 0, player->focusspeed);
		}
		else {
			player->y += player->speed;
			circ_translate(&player->hitbox, 0, player->speed);
			rect_translate(&player->pickupbox, 0, player->speed);
		}
	}
	plyr_animate(player);
}

void plyr_animate(Player *player) {
	if (player->frames > 1) {
		player->animframespast++;
		if (player->animframespast == player->animdelay) {
			player->animframespast = 0;
			player->curframe = (player->curframe + 1) % player->frames;
		}
	}
}

void plyr_close(Player *player) {
	closeScript(&player->script);
	free(player->images);
}