#ifndef ENEMY
#define ENEMY

#include <allegro5\allegro.h>
#include "DanmakuX.h"
#include "Circle.h"
#include "Rectangle.h"
#include "LoadScript.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include <list>
#include <sstream>
#include <string>

typedef struct Enemy {
	std::string type;
	float x, y, width, height, health, maxhealth;
	int frames, curframe, animdelay, animframespast;
	SqBox hitbox;
	ALLEGRO_BITMAP **images;
	bool dead;
	Script script;
	std::list<struct EnemyBullet> bullets;
} Enemy;

typedef struct enem_init_Vals {
	std::string type;
	float px, py, width, height, maxhealth;
	int frames, animdelay;
} enem_init_Vals;

typedef struct enem_position {
	float x, y;
} enem_position;

typedef struct enem_newBullet {
	std::string type;
	bool exists;
	int targeted;
	float srcx, srcy, tgtx, tgty;
} enem_newBullet;

void enem_load(Enemy *enemy, std::string type, float srcx, float srcy);
int enem_init(lua_State *L);
void enem_loadValues(Enemy *enemy);
bool enem_hit(Enemy *enemy, struct PlayerBullet *p);
int enem_recvBullet(lua_State *L);
void enem_addBullet(Enemy * enemy);
void enem_clearBullets(Enemy *enemy);
int enem_getPos(lua_State *L);
int enem_sendHealth(lua_State *L);
int enem_removeBlts(lua_State *L);
int enem_spawnItem(lua_State *L);
int enem_kill(lua_State *L);
void enem_loadPos(Enemy *enemy);
void enem_update(Enemy *enemy);
void enem_animate(Enemy *enemy);
void enem_close(Enemy *enemy);

#endif