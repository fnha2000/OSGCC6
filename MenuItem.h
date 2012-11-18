#ifndef MENUITEM
#define MENUITEM

#include <allegro5\allegro.h>
#include "LoadScript.h"
#include "DanmakuX.h"
#include <sstream>
#include <string>

typedef struct MenuItem {
	float x, y, width, height;
	int frames, curframe, animdelay, animframespast, location;
	ALLEGRO_BITMAP **idleimages;
	ALLEGRO_BITMAP **hlimages;
	ALLEGRO_BITMAP *img;
	Script script;
} MenuItem;

typedef struct MenuItem_Pos {
	float x, y;
} MenuItem_Pos;

typedef struct menuitem_init_Vals {
	std::string type;
	float px, py, width, height;
	int frames, animdelay, location;
} menuitem_init_Vals;

void menuitem_load(MenuItem *item, std::string type);
int menuitem_init(lua_State *L);
void menuitem_loadValues(MenuItem *item);
int menuitem_getPos(lua_State *L);
int menuitem_getLocation(lua_State *L);
void menuitem_loadPos(MenuItem *item);
void menuitem_update(MenuItem *item);
void menuitem_animate(MenuItem *item);
void menuitem_close(MenuItem *item);

#endif