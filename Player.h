#ifndef PLAYER
#define PLAYER

#include <allegro5\allegro.h>
#include "DanmakuX.h"
#include "Circle.h"
#include "Rectangle.h"
#include "LoadScript.h"
#include "EnemyBullet.h"
#include <list>
#include <sstream>
#include <string>

typedef struct Player {
	float x, y, width, height, radius, speed, focusspeed, health, maxhealth;
	int frames, curframe, animdelay, animframespast, fireFront, fireBack, fireSide;
	Circle hitbox;
	SqBox pickupbox;
	ALLEGRO_BITMAP **images;
	bool dead, movel, mover, moveu, moved, shielded, focused, canFire;
	Script script;
} Player;

typedef struct plyr_init_Vals {
	std::string type, bullettype[2];
	float rad, px, py, width, height, mhlth, speed, focusspeed;
	int frames, animdelay;
} plyr_init_Vals;

void plyr_load(Player *player, std::string type);
int plyr_init(lua_State *L);
bool plyr_hit(Player *player, struct EnemyBullet *p);
void plyr_loadValues(Player *player);
int plyr_addBullet(lua_State *L);
int plyr_isFiring(lua_State *L);
int plyr_sendPos(lua_State *L);
void plyr_update(Player *player);
void plyr_animate(Player *player);
void plyr_close(Player *player);

#endif