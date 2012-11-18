#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "LoadScript.h"
#include "ResourceCache.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
 
//int main(int argc, char **argv)
//{
//
//   ALLEGRO_DISPLAY *display = NULL;
// 
//   if(!al_init()) {
//      al_show_native_message_box(display, "Error", "Error", "Failed to initialize Allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
//      return -1;
//   }
// 
//   al_set_new_display_flags(ALLEGRO_WINDOWED);
//   al_set_new_window_position(700, 200);
//   display = al_create_display(800, 600);
//   if(!display) {
//      al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
//      return -1;
//   }
//
//   ResourceCache res;
//   ALLEGRO_BITMAP *img;
//   img = res.get_image("bg.png");
//   if (!img) {
//	   al_show_native_message_box(display, "Error", "Error", "Failed to load image!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
//	   al_destroy_display(display);
//      return -1;
//   }
// 
//   al_clear_to_color(al_map_rgb(0,0,0));
//   al_draw_bitmap(img,100,100,0);
// 
//   al_flip_display();
// 
//   al_rest(10.0);
// 
//   al_destroy_display(display);
//   al_destroy_bitmap(img);
//
//   PHYSFS_deinit();
//	al_shutdown_image_addon();
// 
//   return 0;
//}

int init(lua_State *L) {
	const char *typ = lua_tostring(L, 1);
	const float rad = lua_tonumber(L, 2);
	const float px = lua_tonumber(L, 3);
	const float py = lua_tonumber(L, 4);
	const float wid = lua_tonumber(L, 5);
	const float hgt = lua_tonumber(L, 6);
	const float mhlth = lua_tonumber(L, 7);
	const float spd = lua_tonumber(L, 8);
	const float fcspd = lua_tonumber(L, 9);
	const int frms = lua_tointeger(L, 10);
	const int adelay = lua_tointeger(L, 11);
	const int fdelay = lua_tointeger(L, 12);
	printf("Type: %s\nRadius: %f\nX: %f\nY: %f\nWidth: %f\nHeight: %f\nMax health: %f\nSpeed: %f\nFocus speed: %f\nFrames: %d\nAnim delay: %d\nFire delay: %d", typ, rad, px, py, wid, hgt, mhlth, spd, fcspd, frms, adelay, fdelay);
	return 0;
}

int print(lua_State *L) {
	const char *str = lua_tostring(L, 1);
	printf("%s\n", str);
	return 0;
}

//int main(int argc, char **argv) {
//	Script script;
//	loadScript(&script, "test.lua");
//	lua_CFunction func(init);
//	regFunction(&script, "printToC", func);
//	runFunction(&script, "show");
//}