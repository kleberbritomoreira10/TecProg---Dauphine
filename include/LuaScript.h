#ifndef INCLUDE_LUASCRIPT_H
#define INCLUDE_LUASCRIPT_H

/*
https://github.com/CaioIcy/UnLua
https://github.com/EliasD/unnamed_lua_binder
*/

extern "C" {
	# include <lua.h>
	# include <lauxlib.h>
	# include <lualib.h>
}

#include "Logger.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class LuaScript {

	public:
		LuaScript(const string& filename_);
		virtual ~LuaScript();
		
		vector<int> getIntVector(const string& name_);
		vector<string> getTableKeys(const string& name_);
		bool lua_gettostack(const string& variableName_);

		inline void clean(){
		    int n = lua_gettop(this->luaState);
		    lua_pop(this->luaState, n);
		}

		template<typename T>
		T get(const std::string& variableName_);

		template<typename T>
		T lua_get(const string& variableName_);

		template<typename T>
		T lua_getdefault();

	private:
		lua_State* luaState;
		int level;

};

// Template definitions.
// LuaScript::get

template<typename T>
T LuaScript::get(const std::string& variableName_) {
    if(!luaState) {
        Logger::error("Script is not loaded! [" + variableName_ + "]");
        return lua_getdefault<T>();
    }

    T result;
    if(lua_gettostack(variableName_)) { // variable succesfully on top of stack
        result = lua_get<T>(variableName_);  
    }
    else {
        result = lua_getdefault<T>();
    }


    clean();
    return result;
}

// LuaScript::lua_getdefault

template<typename T>
T LuaScript::lua_getdefault() {
	return 0;
}

// LuaScript::lua_get

template <> 
inline bool LuaScript::lua_get<bool>(const string& variableName_) {
	((void)(variableName_));
	return (bool)lua_toboolean(luaState, -1);
}

template <> 
inline double LuaScript::lua_get<double>(const string& variableName_) {
	if(!lua_isnumber(luaState, -1)) {
		Logger::warning("'" + variableName_ + "' is not a number!");
	}
	return (double)lua_tonumber(luaState, -1);
}

template <>
inline int LuaScript::lua_get<int>(const string& variableName_) {
	if(!lua_isnumber(luaState, -1)) {
		Logger::warning("'" + variableName_ + "' is not a number!");
	}
	return (int)lua_tonumber(luaState, -1);
}

template <>
inline string LuaScript::lua_get<string>(const string& variableName_) {
	string s = "null";
	if(lua_isstring(luaState, -1)) {
		s = string(lua_tostring(luaState, -1));
	} else {
		Logger::warning("'" + variableName_ + "' is not a string!");
	}
	return s;
}

// LuaScript::lua_getdefault

template<>
inline string LuaScript::lua_getdefault<string>() {
	return "null";
}


#endif //INCLUDE_LUASCRIPT_H
