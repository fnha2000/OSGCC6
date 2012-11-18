#include "MenuItem.h"

menuitem_init_Vals menuitemInitVals;
MenuItem_Pos menuitemPos;

void menuitem_load(MenuItem *item, std::string type) {
	std::string filename = "menuitem_" + type + ".lua";
	loadScript(&item->script, filename);
	regFunction(&item->script, "Init", menuitem_init);
	regFunction(&item->script, "updatePos", menuitem_getPos);
	regFunction(&item->script, "getMenuChoice", menuitem_getLocation);
	runFunction(&item->script, "start");
	menuitem_loadValues(item);
}

int menuitem_init(lua_State *L) {
	menuitemInitVals.type = lua_tostring(L, 1);
	menuitemInitVals.px = lua_tonumber(L, 2);
	menuitemInitVals.py = lua_tonumber(L, 3);
	menuitemInitVals.width = lua_tonumber(L, 4);
	menuitemInitVals.height = lua_tonumber(L, 5);
	menuitemInitVals.frames = lua_tointeger(L, 6);
	menuitemInitVals.animdelay = lua_tointeger(L, 7);
	menuitemInitVals.location = lua_tointeger(L, 8);
	lua_pop(L, 8);
	return 0;
}

void menuitem_loadValues(MenuItem *item) {
	item->x = menuitemInitVals.px;
	item->y = menuitemInitVals.py;
	item->width = menuitemInitVals.width;
	item->height = menuitemInitVals.height;
	item->frames = menuitemInitVals.frames;
	item->curframe = item->animframespast = 0;
	item->animdelay = menuitemInitVals.animdelay;
	item->location = menuitemInitVals.location;
	item->idleimages = (ALLEGRO_BITMAP **)malloc(menuitemInitVals.frames * sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < item->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "menuitems/" + menuitemInitVals.type + "/idle/" + out.str() + ".png";
		item->idleimages[i] = dx_getGame()->resources.get_image(filename);
	}
	item->hlimages = (ALLEGRO_BITMAP **)malloc(menuitemInitVals.frames * sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < item->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "menuitems/" + menuitemInitVals.type + "/highlight/" + out.str() + ".png";
		item->hlimages[i] = dx_getGame()->resources.get_image(filename);
	}
	item->img = item->idleimages[0];
}

int menuitem_getPos(lua_State *L) {
	menuitemPos.x = lua_tonumber(L, 1);
	menuitemPos.y = lua_tonumber(L, 2);
	lua_pop(L, 2);
	return 0;
}

int menuitem_getLocation(lua_State *L) {
	lua_pushinteger(L, dx_getGame()->menuChoice);
	return 1;
}

void menuitem_loadPos(MenuItem *item) {
	item->x = menuitemPos.x;
	item->y = menuitemPos.y;
}

void menuitem_update(MenuItem *item) {
	runFunction(&item->script, "update");
	menuitem_loadPos(item);
	menuitem_animate(item);
}

void menuitem_animate(MenuItem *item) {
	if (item->frames > 1) {
		item->animframespast++;
		if (item->animframespast == item->animdelay) {
			item->animframespast = 0;
			item->curframe = (item->curframe + 1) % item->frames;
		}
	}
	if (dx_getGame()->menuChoice == item->location) item->img = item->hlimages[item->curframe];
	else item->img = item->idleimages[item->curframe];
}

void menuitem_close(MenuItem *item) {
	closeScript(&item->script);
	free(item->hlimages);
	free(item->idleimages);
}