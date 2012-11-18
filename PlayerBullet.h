#ifndef PLAYERBULLET
#define PLAYERBULLET

#include <allegro5\allegro.h>
#include "Rectangle.h"
#include "Enemy.h"
#include "LoadScript.h"
#include <sstream>
#include <string>

typedef struct PlayerBullet {
	float x, y, width, height, damage;
	int frames, curframe, animdelay, animframespast;
	SqBox hitbox;
	ALLEGRO_BITMAP **images;
	bool dead;
	Script script;
} PlayerBullet;

typedef struct PlrBlt_Pos {
	float x, y;
} PlrBlt_Pos;

typedef struct plblt_init_Vals {
	std::string type;
	float px, py, width, height, damage;
	int frames, animdelay;
} plblt_init_Vals;

void plblt_load(PlayerBullet *blt, std::string type, float srcx, float srcy, float tgtx, float tgty);
int plblt_init(lua_State *L);
void plblt_loadValues(PlayerBullet *blt);
bool plblt_hit(PlayerBullet *blt, struct Enemy *e);
int plblt_getPos(lua_State *L);
void plblt_loadPos(PlayerBullet *blt);
void plblt_update(PlayerBullet *blt);
void plblt_animate(PlayerBullet *blt);
void plblt_close(PlayerBullet *blt);

#endif