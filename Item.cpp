#include "Item.h"

item_init_Vals itemInitVals;
Item_Pos itemPos;

void item_load(Item *item, std::string type) {
	std::string filename = "item_" + type + ".lua";
	loadScript(&item->script, filename);
	regFunction(&item->script, "init", item_init);
	regFunction(&item->script, "updatePos", item_getPos);
	runFunction(&item->script, "start");
	item_loadValues(item);
}

int item_init(lua_State *L) {
	itemInitVals.type = lua_tostring(L, 1);
	itemInitVals.px = lua_tonumber(L, 2);
	itemInitVals.py = lua_tonumber(L, 3);
	itemInitVals.width = lua_tonumber(L, 4);
	itemInitVals.height = lua_tonumber(L, 5);
	itemInitVals.frames = lua_tointeger(L, 6);
	itemInitVals.animdelay = lua_tointeger(L, 7);
	lua_pop(L, 7);
	return 0;
}

void item_loadValues(Item *item) {
	item->x = itemInitVals.px;
	item->y = itemInitVals.py;
	item->width = itemInitVals.width;
	item->height = itemInitVals.height;
	item->frames = itemInitVals.frames;
	item->curframe = item->animframespast = 0;
	item->animdelay = itemInitVals.animdelay;
	item->dead = false;
	rect_init(&item->hitbox, item->x, item->y, item->width, item->height);
	item->images = (ALLEGRO_BITMAP **)malloc(itemInitVals.frames * sizeof(ALLEGRO_BITMAP *));
	for (int i = 0; i < item->frames; i++) {
		std::stringstream out;
		out << i;
		std::string filename = "item/" + itemInitVals.type + "/" + out.str() + ".png";
		item->images[i] = dx_getGame()->resources.get_image(filename);
	}
}

bool item_hit(Item *item, Player *p) {
	if (!item->dead) {
		if (rect_intersects(&item->hitbox, &p->pickupbox)) return true;
	}
	return false;
}

int item_getPos(lua_State *L) {
	itemPos.x = lua_tonumber(L, 1);
	itemPos.y = lua_tonumber(L, 2);
	lua_pop(L, 2);
	return 0;
}

void item_loadPos(Item *item) {
	item->x += itemPos.x;
	item->y += itemPos.y;
	rect_translate(&item->hitbox, itemPos.x, itemPos.y);
}

void item_update(Item *item) {
	runFunction(&item->script, "update");
	item_loadPos(item);
	item_animate(item);
}

void item_animate(Item *item) {
	if (item->frames > 1) {
		item->animframespast++;
		if (item->animframespast == item->animdelay) {
			item->animframespast = 0;
			item->curframe = (item->curframe + 1) % item->frames;
		}
	}
}

void item_close(Item *item) {
	closeScript(&item->script);
	free(item->images);
}