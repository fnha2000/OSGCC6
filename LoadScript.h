#ifndef LOADSCRIPT
#define LOADSCRIPT

#pragma once
#pragma comment(lib, "lua51.lib")

#include <cstdio>
#include <string>
#include <functional>
#include <lua.hpp>

typedef struct Script {
	lua_State *luaState;
	bool running;
} Script;

bool loadScript(Script *script, std::string file);
void regFunction(Script *script, std::string regname, lua_CFunction func);
void runFunction(Script *script, std::string func);
void runFunction(Script *script, std::string func, std::string obj);
void runFunction(Script *script, std::string func, lua_Integer obj);
void runFunction(Script *script, std::string func, lua_Number srcx, lua_Number srcy, lua_Number tgtx, lua_Number tgty);
void closeScript(Script *script);

#endif