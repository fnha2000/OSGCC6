#include "DanmakuX.h"

float FPS = 60.0;
bool redraw;
Player playerset;
DanmakuX danmakux;
ALLEGRO_DISPLAY* display;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_BITMAP *UI;

DanmakuX *dx_getGame() {
	return &danmakux;
}

void init(int width, int height) {
	danmakux.width = width;
	danmakux.height = height;

	if (!al_init()) al_show_native_message_box(display, "Error", "Error", "Failed to initialize Allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	
	if (!al_install_keyboard()) al_show_native_message_box(display, "Error", "Error", "Failed to install keyboard!", NULL, ALLEGRO_MESSAGEBOX_ERROR);

	if (!al_install_audio()) al_show_native_message_box(display, "Error", "Error", "Failed to install audio!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	
	if (!al_reserve_samples(10)) al_show_native_message_box(display, "Error", "Error", "Failed to reserve samples!", NULL, ALLEGRO_MESSAGEBOX_ERROR);

	timer = al_create_timer(1.0 / FPS);
	if (!timer) al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	al_set_new_window_position(700, 200);
	display = al_create_display(danmakux.width, danmakux.height);
	if (!display) al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);

	event_queue = al_create_event_queue();
	if (!event_queue) al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	redraw = false;
	danmakux.fireBomb = false;
	danmakux.lives = 2;
	danmakux.bombsRemain = 2;
	danmakux.weaponLevel = 1;
	danmakux.done = false;
	danmakux.state_menu = true;
	danmakux.state_paused = false;
	danmakux.state_playing = false;
	danmakux.state_dialog = false;
	danmakux.menuChoice = 0;
	danmakux.currentLevel = 1;
	danmakux.player = &playerset;
	UI = danmakux.resources.get_image("ui.png");

	al_start_timer(timer);
	loadMenu("mainmenu");
	/*danmakux.state_menu = false;
							danmakux.state_playing = true;
							danmakux.state_paused = false;
							loadLevel("level1");*/
	al_play_sample(danmakux.bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void loadLevel(std::string lvl) {
	clearMenu();
	clearPause();
	buildPause();
	danmakux.framesPast = 0;
	if (danmakux.menu.running) closeScript(&danmakux.menu);
	if (danmakux.level.running) closeScript(&danmakux.level);
	std::string filename = "lvl_" + lvl + ".lua";
	loadScript(&danmakux.level, filename);
	regFunction(&danmakux.level, "setBGM", setBGM);
	regFunction(&danmakux.level, "setBG", setBG);
	regFunction(&danmakux.level, "addEnemy", addEnemy);
	regFunction(&danmakux.level, "elapsedTime", timePassed);
	regFunction(&danmakux.level, "win", winLevel);
	runFunction(&danmakux.level, "start");
	al_stop_samples();
	al_play_sample(danmakux.bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void loadMenu(std::string menu) {
	clearMenu();
	danmakux.menuChoice = 0;
	if (danmakux.level.running) closeScript(&danmakux.level);
	std::string menufile = menu + ".lua";
	loadScript(&danmakux.menu, menufile);
	regFunction(&danmakux.menu, "addMenuChoice", addMenuItem);
	regFunction(&danmakux.menu, "setBGM", setBGM);
	regFunction(&danmakux.menu, "setBG", setBG);
	runFunction(&danmakux.menu, "start");
}

int setBGM(lua_State *L) {
	std::string bgmfile = lua_tostring(L, 1);
	lua_pop(L, 1);
	danmakux.bgm = danmakux.resources.get_sound(bgmfile);
	return 0;
}

int setBG(lua_State *L) {
	std::string bgfile = lua_tostring(L, 1);
	int scrollable = lua_tointeger(L, 2);
	if (scrollable == 1) {
		danmakux.bgscroll = true;
		danmakux.bgheight = lua_tonumber(L, 3);
	}
	else {
		danmakux.bgscroll = false;
	}
	lua_pop(L, 3);
	danmakux.bgimg = danmakux.resources.get_image(bgfile);
	return 0;
}

int timePassed(lua_State *L) {
	lua_pushinteger(L, danmakux.framesPast);
	return 1;
}

void setPlayer(std::string type) {
	plyr_close(danmakux.player);
	plyr_load(danmakux.player, type);
}

int addMenuItem(lua_State *L) {
	std::string type = lua_tostring(L, 1);
	lua_pop(L, 1);
	MenuItem newItem;
	menuitem_load(&newItem, type);
	danmakux.menuitems.push_back(newItem);
	return 0;
}

void addPauseItem(std::string type) {
	MenuItem newItem;
	menuitem_load(&newItem, type);
	danmakux.pauseitems.push_back(newItem);
}

void addItem(std::string type) {
	Item newItem;
	item_load(&newItem, type);
	danmakux.items.push_back(newItem);
}

int addEnemy(lua_State *L) {
	std::string type = lua_tostring(L, 1);
	float srcx = lua_tonumber(L, 2);
	float srcy = lua_tonumber(L, 3);
	lua_pop(L, 3);
	Enemy newenemy;
	enem_load(&newenemy, type, srcx, srcy);
	danmakux.enemies.push_back(newenemy);
	return 0;
}

int winLevel(lua_State *L) {
	danmakux.currentLevel++;
	std::stringstream levelno;
	levelno << danmakux.currentLevel;
	std::string level = "level" + levelno.str();
	loadLevel(level);
	return 0;
}

void clearMenu() {
	danmakux.menuitems.clear();
}

void clearPause() {
	danmakux.pauseitems.clear();
}

void buildPause() {
	//build pause menu
}

void shutdown() {
	if (timer) al_destroy_timer(timer);
	if (display) al_destroy_display(display);
	if (event_queue) al_destroy_event_queue(event_queue);
	exit(0);
}

void update() {
	if (!danmakux.state_paused && danmakux.state_playing) {
		danmakux.framesPast++;
		runFunction(&danmakux.level, "update");
		for (std::list<PlayerBullet>::iterator i = danmakux.playerbullets.begin(); i != danmakux.playerbullets.end(); i++) {
			plblt_update(&(*i));
		}
		for (std::list<Enemy>::iterator i = danmakux.enemies.begin(); i != danmakux.enemies.end(); i++) {
			if (!(*i).dead) enem_update(&(*i));
			for (std::list<EnemyBullet>::iterator j = (*i).bullets.begin(); j != (*i).bullets.end(); j++) {
				enblt_update(&(*j));
			}
		}
		for (std::list<Item>::iterator i = danmakux.items.begin(); i != danmakux.items.end(); i++) {
			item_update(&(*i));
		}
		plyr_update(danmakux.player);
		if (danmakux.bombsRemain > 0 && danmakux.fireBomb == true) {
			danmakux.fireBomb = false;
			//bomb
		}
	}
	else if (danmakux.state_paused) {
		for (std::list<MenuItem>::iterator i = danmakux.pauseitems.begin(); i != danmakux.pauseitems.end(); i++) {
			menuitem_update(&(*i));
		}
	}
	else if (danmakux.state_menu) {
		for (std::list<MenuItem>::iterator i = danmakux.menuitems.begin(); i != danmakux.menuitems.end(); i++) {
			menuitem_update(&(*i));
		}
	}
}

void redrawDisp() {
	al_clear_to_color(al_map_rgb(0,0,0));
	if (danmakux.state_playing) {
		std::list<std::list<EnemyBullet> *> enblts;
		al_draw_bitmap(danmakux.bgimg,0,0,0);
		for (std::list<PlayerBullet>::iterator i = danmakux.playerbullets.begin(); i != danmakux.playerbullets.end(); i++) {
			if (!(*i).dead) {
				al_draw_bitmap((*i).images[(*i).curframe], (*i).x, (*i).y, 0);
			}
		}
		for (std::list<Enemy>::iterator i = danmakux.enemies.begin(); i != danmakux.enemies.end(); i++) {
			if (!(*i).dead) {
				al_draw_bitmap((*i).images[(*i).curframe], (*i).x, (*i).y, 0);
				enblts.push_back(&(*i).bullets);
			}
		}
		for (std::list<Item>::iterator i = danmakux.items.begin(); i != danmakux.items.end(); i++) {
			if (!(*i).dead) {
				al_draw_bitmap((*i).images[(*i).curframe], (*i).x, (*i).y, 0);
			}
		}
		al_draw_bitmap(danmakux.player->images[danmakux.player->curframe], danmakux.player->x, danmakux.player->y, 0);
		for (std::list<std::list<EnemyBullet> *>::iterator i = enblts.begin(); i != enblts.end(); i++) {
			for (std::list<EnemyBullet>::iterator j = (*i)->begin(); j != (*i)->end(); j++) {
				al_draw_bitmap((*j).images[(*j).curframe], (*j).x, (*j).y, 0);
			}
		}
		//drawUI();
		if (danmakux.state_paused) {
			for (std::list<MenuItem>::iterator i = danmakux.pauseitems.begin(); i != danmakux.pauseitems.end(); i++) {
				al_draw_bitmap((*i).img, (*i).x, (*i).y, 0);
			}
		}
	}
	else if (danmakux.state_menu) {
		al_draw_bitmap(danmakux.bgimg,0,0,0);
		for (std::list<MenuItem>::iterator i = danmakux.menuitems.begin(); i != danmakux.menuitems.end(); i++) {
			al_draw_bitmap((*i).img, (*i).x, (*i).y, 0);
		}
	}
	al_flip_display();
}

void gameloop() {
	while (!danmakux.done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			update();
			gameLogic();
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			danmakux.done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (danmakux.state_playing && !danmakux.state_paused) {
				switch (ev.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						danmakux.player->moveu = true;
						break;
					case ALLEGRO_KEY_DOWN:
						danmakux.player->moved = true;
						break;
					case ALLEGRO_KEY_LEFT:
						danmakux.player->movel = true;
						break;
					case ALLEGRO_KEY_RIGHT:
						danmakux.player->mover = true;
						break;
					case ALLEGRO_KEY_Z:
						danmakux.player->fireFront = 1;
						break;
					case ALLEGRO_KEY_X:
						danmakux.player->fireBack = 1;
						break;
					case ALLEGRO_KEY_C:
						danmakux.player->fireSide = 1;
						break;
					case ALLEGRO_KEY_LSHIFT:
						danmakux.player->focused = true;
						break;
					case ALLEGRO_KEY_ESCAPE:
						break;
				}
			}
			else if (danmakux.state_menu) {
				std::stringstream levelno;
				std::string level;
				switch (ev.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						danmakux.menuChoice -= 1;
						if (danmakux.menuChoice < 0) danmakux.menuChoice = danmakux.menuitems.size()-1;
						break;
					case ALLEGRO_KEY_DOWN:
						danmakux.menuChoice = (danmakux.menuChoice + 1) % danmakux.menuitems.size();
						break;
					case ALLEGRO_KEY_LEFT:
						danmakux.menuChoice -= 1;
						if (danmakux.menuChoice < 0) danmakux.menuChoice = danmakux.menuitems.size()-1;
						break;
					case ALLEGRO_KEY_RIGHT:
						danmakux.menuChoice = (danmakux.menuChoice + 1) % danmakux.menuitems.size();
						break;
					case ALLEGRO_KEY_Z:
						switch (danmakux.menuChoice) {
						case 0:
							clearMenu();
							danmakux.state_menu = false;
							danmakux.state_playing = true;
							danmakux.state_paused = false;
							danmakux.state_dialog = false;
							levelno << danmakux.currentLevel;
							level = "level" + levelno.str();
							plyr_load(danmakux.player, "machine");
							loadLevel(level);
							break;
						case 1:
							break;
						case 2:
							danmakux.done = true;
							break;
						}
						break;
					case ALLEGRO_KEY_X:
						danmakux.menuChoice = 2;
						break;
				}
			}
			else if (danmakux.state_paused) {
				switch (ev.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						danmakux.menuChoice -= 1;
						if (danmakux.menuChoice < 0) danmakux.menuChoice = danmakux.pauseitems.size()-1;
						break;
					case ALLEGRO_KEY_DOWN:
						danmakux.menuChoice = (danmakux.menuChoice + 1) % danmakux.pauseitems.size();
						break;
					case ALLEGRO_KEY_LEFT:
						danmakux.menuChoice -= 1;
						if (danmakux.menuChoice < 0) danmakux.menuChoice = danmakux.pauseitems.size()-1;
						break;
					case ALLEGRO_KEY_RIGHT:
						danmakux.menuChoice = (danmakux.menuChoice + 1) % danmakux.pauseitems.size();
						break;
					case ALLEGRO_KEY_Z:
						break;
					case ALLEGRO_KEY_X:
						danmakux.fireBomb = true;
						break;
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (danmakux.state_playing && !danmakux.state_paused) {
				switch (ev.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						danmakux.player->moveu = false;
						break;
					case ALLEGRO_KEY_DOWN:
						danmakux.player->moved = false;
						break;
					case ALLEGRO_KEY_LEFT:
						danmakux.player->movel = false;
						break;
					case ALLEGRO_KEY_RIGHT:
						danmakux.player->mover = false;
						break;
					case ALLEGRO_KEY_Z:
						danmakux.player->fireFront = 0;
						break;
					case ALLEGRO_KEY_X:
						danmakux.player->fireBack = 0;
						break;
					case ALLEGRO_KEY_C:
						danmakux.player->fireSide = 0;
						break;
					case ALLEGRO_KEY_LSHIFT:
						danmakux.player->focused = false;
						break;
				}
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redrawDisp();
		}
	}
}

void drawUI() {
	al_draw_bitmap(UI, 700, 0, 0);
}

void gameLogic() {
	if (danmakux.player->x < 0) {
		if (danmakux.player->focused) danmakux.player->x += danmakux.player->focusspeed;
		else danmakux.player->x += danmakux.player->speed;
	}
	if (danmakux.player->x > danmakux.width-danmakux.player->width) {
		if (danmakux.player->focused) danmakux.player->x -= danmakux.player->focusspeed;
		else danmakux.player->x -= danmakux.player->speed;
	}
	if (danmakux.player->y < 0) {
		if (danmakux.player->focused) danmakux.player->y += danmakux.player->focusspeed;
		else danmakux.player->y += danmakux.player->speed;
	}
	if (danmakux.player->y > danmakux.height-danmakux.player->height) {
		if (danmakux.player->focused) danmakux.player->y -= danmakux.player->focusspeed;
		else danmakux.player->y -= danmakux.player->speed;
	}
	for (std::list<PlayerBullet>::iterator i = danmakux.playerbullets.begin(); i != danmakux.playerbullets.end(); i++) {
		for (std::list<Enemy>::iterator j = danmakux.enemies.begin(); j != danmakux.enemies.end(); j++) {
			if (rect_intersects(&(*j).hitbox, &(*i).hitbox)) {
				(*j).health -= (*i).damage;
				plblt_close(&(*i));
				i = danmakux.playerbullets.erase(i);
				for (std::list<EnemyBullet>::iterator k = (*j).bullets.begin(); k != (*j).bullets.end(); k++) {
					if (circ_intersects(&(*k).hitbox, &danmakux.player->hitbox)) {
						danmakux.player->health -= (*k).damage;
						enblt_close(&(*k));
						k = (*j).bullets.erase(k);
					}
					if ((*k).x < 0 || (*k).y < 0 || (*k).x > danmakux.width || (*k).y > danmakux.height) {
						enblt_close(&(*k));
						k = (*j).bullets.erase(k);
					}
				}
				if ((*j).health <= 0) {
					(*j).dead = true;
					addItem("powerup");
				}
				if ((*j).dead && (*j).bullets.empty()) {
					enem_close(&(*j));
					j = danmakux.enemies.erase(j);
				}
			}
		}
		if ((*i).x+(*i).width < 0 || (*i).y+(*i).height < 0 || (*i).x > danmakux.width || (*i).y > danmakux.height || (*i).dead) {
			plblt_close(&(*i));
			i = danmakux.playerbullets.erase(i);
		}
	}
	if (danmakux.player->health <= 0) {
		danmakux.player->dead = true;
		//dying procedure
	}
	for (std::list<Item>::iterator i = danmakux.items.begin(); i != danmakux.items.end(); i++) {
		if ((*i).type == "wall") {
			if (danmakux.player->moveu && danmakux.player->y < (*i).y+(*i).height && danmakux.player->x > (*i).x && danmakux.player->x < (*i).x+(*i).width) {
				if (danmakux.player->focused) {
					danmakux.player->y += danmakux.player->focusspeed;
				}
				else {
					danmakux.player->y += danmakux.player->speed;
				}
			}
			if (danmakux.player->moved && danmakux.player->y > (*i).y && danmakux.player->x > (*i).x && danmakux.player->x < (*i).x+(*i).width) {
				if (danmakux.player->focused) {
					danmakux.player->y -= danmakux.player->focusspeed;
				}
				else {
					danmakux.player->y -= danmakux.player->speed;
				}
			}
			if (danmakux.player->movel && danmakux.player->x < (*i).x+(*i).width && danmakux.player->y > (*i).y && danmakux.player->y < (*i).y+(*i).height) {
				if (danmakux.player->focused) {
					danmakux.player->x += danmakux.player->focusspeed;
				}
				else {
					danmakux.player->x += danmakux.player->speed;
				}
			}
			if (danmakux.player->mover && danmakux.player->x > (*i).x && danmakux.player->y > (*i).y && danmakux.player->y < (*i).y+(*i).height) {
				if (danmakux.player->focused) {
					danmakux.player->x -= danmakux.player->focusspeed;
				}
				else {
					danmakux.player->x -= danmakux.player->speed;
				}
			}
		}
		if (rect_intersects(&(*i).hitbox, &danmakux.player->pickupbox)) {
			if ((*i).type == "powerup") {
				runFunction(&danmakux.player->script, "powerup");
			}
			item_close(&(*i));
			i = danmakux.items.erase(i);
		}
	}
}

int main() {
	init(800, 600);
	gameloop();
	shutdown();
}