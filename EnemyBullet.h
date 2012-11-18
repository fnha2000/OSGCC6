#ifndef ENEMYBULLET
#define ENEMYBULLET

#include <allegro5\allegro.h>
#include "DanmakuX.h"
#include "Circle.h"
#include "Player.h"
#include "LoadScript.h"
#include <sstream>
#include <string>

typedef struct EnemyBullet {
	float x, y, radius, damage;
	int frames, curframe, animdelay, animframespast;
	Circle hitbox;
	ALLEGRO_BITMAP **images;
	bool dead;
	Script script;
} EnemyBullet;

typedef struct EnBlt_Pos {
	float x, y;
} EnBlt_Pos;

typedef struct enblt_init_Vals {
	std::string type;
	float px, py, radius, damage;
	int frames, animdelay;
} enblt_init_Vals;

void enblt_load(EnemyBullet *blt, std::string type, float srcx, float srcy, float tgtx, float tgty);
int enblt_init(lua_State *L);
void enblt_loadValues(EnemyBullet *blt);
bool enblt_hit(EnemyBullet *blt, struct Player *p);
int enblt_getPos(lua_State *L);
void enblt_loadPos(EnemyBullet *blt);
void enblt_update(EnemyBullet *blt);
void enblt_animate(EnemyBullet *blt);
void enblt_close(EnemyBullet *blt);

#endif