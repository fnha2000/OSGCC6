#include "PlayerBullet.h"

plblt_init_Vals plbltInitVals;
PlrBlt_Pos plbltPos;
bool bltkill = false;

void plblt_load(PlayerBullet *blt, std::string type, float srcx, float srcy, float tgtx, float tgty) {
	std::string filename = "plblt_" + type + ".lua";
	loadScript(&blt->script, filename);
	regFunction(&blt->script, "init", plblt_init);
	regFunction(&blt->script, "updatePos", plblt_getPos);
	regFunction(&blt->script, "kill", plblt_kill);
	runFunction(&blt->script, "start", srcx, srcy, tgtx, tgty);
	plblt_loadValues(blt);
}

int plblt_init(lua_State *L) {
	plbltInitVals.type = lua_tostring(L, 1);
	plbltInitVals.px = lua_tonumber(L, 2);
	plbltInitVals.py = lua_tonumber(L, 3);
	plbltInitVals.width = lua_tonumber(L, 4);
	plbltInitVals.height = lua_tonumber(L, 5);
	plbltInitVals.damage = lua_tonumber(L, 6);
	plbltInitVals.frames = lua_tointeger(L, 7);
	plbltInitVals.animdelay = lua_tointeger(L, 8);
	lua_pop(L, 8);
	return 0;
}

void plblt_loadValues(PlayerBullet *blt) {
	blt->x = plbltInitVals.px;
	blt->y = plbltInitVals.py;
	blt->width = plbltInitVals.width;
	blt->height = plbltInitVals.height;
	blt->damage = plbltInitVals.damage;
	blt->frames = plbltInitVals.frames;
	blt->curframe = blt->animframespast = 0;
	blt->animdelay = plbltInitVals.animdelay;
	blt->dead = false;
	rect_init(&blt->hitbox, blt->x, blt->y, blt->width, blt->height);
	blt->images = (ALLEGRO_BITMAP **)malloc(plbltInitVals.frames * sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < blt->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "playerbullets/" + plbltInitVals.type + "/" + out.str() + ".png";
		blt->images[i] = dx_getGame()->resources.get_image(filename);
	}
}

bool plblt_hit(PlayerBullet *blt, Enemy *e) {
	if (!blt->dead) {
		if (rect_intersects(&blt->hitbox, &e->hitbox)) return true;
	}
	return false;
}

int plblt_kill(lua_State *L) {
	bltkill = true;
	return 0;
}

int plblt_getPos(lua_State *L) {
	plbltPos.x = lua_tonumber(L, 1);
	plbltPos.y = lua_tonumber(L, 2);
	lua_pop(L, 2);
	return 0;
}

void plblt_loadPos(PlayerBullet *blt) {
	blt->x += plbltPos.x;
	blt->y += plbltPos.y;
	rect_translate(&blt->hitbox, plbltPos.x, plbltPos.y);
}

void plblt_update(PlayerBullet *blt) {
	runFunction(&blt->script, "update");
	if (bltkill) {
		bltkill = false;
		blt->dead = true;
	}
	plblt_loadPos(blt);
	plblt_animate(blt);
}

void plblt_animate(PlayerBullet *blt) {
	if (blt->frames > 1) {
		blt->animframespast++;
		if (blt->animframespast == blt->animdelay) {
			blt->animframespast = 0;
			blt->curframe = (blt->curframe + 1) % blt->frames;
		}
	}
}

void plblt_close(PlayerBullet *blt) {
	closeScript(&blt->script);
	free(blt->images);
}