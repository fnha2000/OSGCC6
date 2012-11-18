#ifndef DANMAKUX
#define DANMAKUX

#include <allegro5\allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <cstdio>
#include <sstream>
#include <list>
#include "Player.h"
#include "LoadScript.h"
#include "ResourceCache.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Item.h"
#include "MenuItem.h"

typedef struct DanmakuX {
	int width, height, menuChoice, framesPast, lives, bombsRemain, weaponLevel, currentLevel;
	bool done, state_menu, state_paused, state_playing, state_dialog;
	bool bgscroll, fireBomb;
	float bgheight;
	ResourceCache resources;
	Script menu, level;
	Player *player;
	ALLEGRO_BITMAP *bgimg;
	ALLEGRO_SAMPLE *bgm;
	std::list<struct Enemy> enemies;
	std::list<struct PlayerBullet> playerbullets;
	std::list<struct Item> items;
	std::list<struct MenuItem> menuitems;
	std::list<struct MenuItem> pauseitems;
} DanmakuX;

DanmakuX *dx_getGame();
void init(int width, int height);
void loadLevel(std::string lvl);
void loadMenu(std::string menu);
int setBGM(lua_State *L);
int setBG(lua_State *L);
int timePassed(lua_State *L);
void setPlayer(std::string type);
int addMenuItem(lua_State *L);
int addEnemy(lua_State *L);
int winLevel(lua_State *L);
void addPauseItem(std::string type);
void addItem(std::string type);
void clearMenu();
void clearPause();
void buildPause();
void shutdown();
void gameloop();
void update();
void redrawDisp();
void drawUI();
void gameLogic();

#endif

/*
Multi fire
Bomb
Transition
*/