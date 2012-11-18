#ifndef ITEM
#define ITEM

#include <allegro5\allegro.h>
#include "DanmakuX.h"
#include "Rectangle.h"
#include "LoadScript.h"
#include "Player.h"
#include <sstream>
#include <string>

typedef struct Item {
	std::string type;
	float x, y, width, height;
	int frames, curframe, animdelay, animframespast;
	SqBox hitbox;
	ALLEGRO_BITMAP **images;
	bool dead;
	Script script;
} Item;

typedef struct Item_Pos {
	float x, y;
} Item_Pos;

typedef struct item_init_Vals {
	std::string type;
	float px, py, width, height;
	int frames, animdelay;
} item_init_Vals;

void item_load(Item *item, std::string type);
int item_init(lua_State *L);
void item_loadValues(Item *item);
bool item_hit(Item *item, struct Player *p);
int item_getPos(lua_State *L);
void item_loadPos(Item *item);
void item_update(Item *item);
void item_animate(Item *item);
void item_close(Item *item);

#endif