#include "EnemyBullet.h"

enblt_init_Vals enbltInitVals;
EnBlt_Pos enbltPos;

void enblt_load(EnemyBullet *blt, std::string type, float srcx, float srcy, float tgtx, float tgty) {
	std::string filename = "enblt_" + type + ".lua";
	loadScript(&blt->script, filename);
	regFunction(&blt->script, "init", enblt_init);
	regFunction(&blt->script, "updatePos", enblt_getPos);
	runFunction(&blt->script, "start", srcx, srcy, tgtx, tgty);
	enblt_loadValues(blt);
}

int enblt_init(lua_State *L) {
	enbltInitVals.type = lua_tostring(L, 1);
	enbltInitVals.px = lua_tonumber(L, 2);
	enbltInitVals.py = lua_tonumber(L, 3);
	enbltInitVals.radius = lua_tonumber(L, 4);
	enbltInitVals.damage = lua_tonumber(L, 5);
	enbltInitVals.frames = lua_tointeger(L, 6);
	enbltInitVals.animdelay = lua_tointeger(L, 7);
	lua_pop(L, 7);
	return 0;
}

void enblt_loadValues(EnemyBullet *blt) {
	blt->x = enbltInitVals.px;
	blt->y = enbltInitVals.py;
	blt->radius = enbltInitVals.radius;
	blt->damage = enbltInitVals.damage;
	blt->frames = enbltInitVals.frames;
	blt->curframe = blt->animframespast = 0;
	blt->animdelay = enbltInitVals.animdelay;
	blt->dead = false;
	circ_init(&blt->hitbox, (blt->x + blt->radius), (blt->y + blt->radius), blt->radius);
	blt->images = (ALLEGRO_BITMAP **)malloc(enbltInitVals.frames + sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < blt->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "enemybullets/" + enbltInitVals.type + "/" + out.str() + ".png";
		blt->images[i] = dx_getGame()->resources.get_image(filename);
	}
}

bool enblt_hit(EnemyBullet *blt, Player *p) {
	if (!blt->dead) {
		if (circ_intersects(&blt->hitbox, &p->hitbox)) return true;
	}
	return false;
}

int enblt_getPos(lua_State *L) {
	enbltPos.x = lua_tonumber(L, 1);
	enbltPos.y = lua_tonumber(L, 2);
	lua_pop(L, 2);
	return 0;
}

void enblt_loadPos(EnemyBullet *blt) {
	blt->x += enbltPos.x;
	blt->y += enbltPos.y;
	circ_translate(&blt->hitbox, enbltPos.x, enbltPos.y);
}

void enblt_update(EnemyBullet *blt) {
	runFunction(&blt->script, "update");
	enblt_loadPos(blt);
	enblt_animate(blt);
}

void enblt_animate(EnemyBullet *blt) {
	if (blt->frames > 1) {
		blt->animframespast++;
		if (blt->animframespast == blt->animdelay) {
			blt->animframespast = 0;
			blt->curframe = (blt->curframe + 1) % blt->frames;
		}
	}
}

void enblt_close(EnemyBullet *blt) {
	closeScript(&blt->script);
	free(blt->images);
}