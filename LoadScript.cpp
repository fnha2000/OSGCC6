#include "LoadScript.h"
#include <Windows.h>

using namespace std;

bool loadScript(Script *script, std::string file) {
	script->luaState = luaL_newstate();
	luaL_openlibs(script->luaState);
	std::string filename("scripts/");
	filename.append(file);
	try {
		luaL_dofile(script->luaState, filename.c_str());
	} catch (...) {
		printf("Error in script %s\n", file.c_str());
		return false;
	}
	script->running = true;
	return true;
}

void regFunction(Script *script, std::string regname, lua_CFunction func) {
	lua_register(script->luaState, regname.c_str(), func);
}

void runFunction(Script *script, std::string func) {
	lua_getglobal(script->luaState, func.c_str());
	if (lua_pcall(script->luaState, 0, 0, 0) != 0) {
		std::string error = lua_tostring(script->luaState, 1);
		printf("%s\n", error.c_str());
	}
}

void runFunction(Script *script, std::string func, std::string obj) {
	lua_getglobal(script->luaState, func.c_str());
	lua_pushstring(script->luaState, obj.c_str());
	if (lua_pcall(script->luaState, 1, 0, 0)) {
		std::string error = lua_tostring(script->luaState, 1);
		printf("%s\n", error.c_str());
	}
}

void runFunction(Script *script, std::string func, lua_Integer obj) {
	lua_getglobal(script->luaState, func.c_str());
	lua_pushinteger(script->luaState, obj);
	if (lua_pcall(script->luaState, 1, 0, 0)) {
		std::string error = lua_tostring(script->luaState, 1);
		printf("%s\n", error.c_str());
	}
}

void runFunction(Script *script, std::string func, lua_Number srcx, lua_Number srcy, lua_Number tgtx, lua_Number tgty) {
	lua_getglobal(script->luaState, func.c_str());
	lua_pushnumber(script->luaState, srcx);
	lua_pushnumber(script->luaState, srcy);
	lua_pushnumber(script->luaState, tgtx);
	lua_pushnumber(script->luaState, tgty);
	if (lua_pcall(script->luaState, 4, 0, 0)) {
		std::string error = lua_tostring(script->luaState, 1);
		printf("%s\n", error.c_str());
	}
}

void closeScript(Script *script) {
	lua_close(script->luaState);
	script->running = false;
}