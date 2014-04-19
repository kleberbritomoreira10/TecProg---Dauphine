#include "LuaScript.h"
#include "Logger.h"

/*
https://github.com/CaioIcy/UnLua
https://github.com/EliasD/unnamed_lua_binder
*/

LuaScript::LuaScript(const string& filename_) {
    /// @todo Log an error message for different lua error codes.
    this->level = 0;
    this->luaState = luaL_newstate();

    const int loadedFile = luaL_loadfile(this->luaState, filename_.c_str());
    const int calledFunction = lua_pcall(luaState, 0, 0, 0);

    if (loadedFile == LUA_OK && calledFunction == LUA_OK) {
        if(this->luaState != nullptr){
            luaL_openlibs(this->luaState);
        }
    }
    else{
        Logger::error("Failed to load (" + filename_ + ")");
        this->luaState = nullptr;
    }

}

LuaScript::~LuaScript() {
    if(this->luaState != nullptr){
        lua_close(this->luaState);
    }
    this->level = 0;
}

vector<int> LuaScript::unlua_getIntVector(const string& name_) {
    vector<int> intVector;

    const bool gotToStack = unlua_getToStack(name_);
    const bool arrayNotFound = lua_isnil(this->luaState, -1);
    if(gotToStack && arrayNotFound){

        lua_pushnil(this->luaState);
        while(lua_next(this->luaState, -2)) {
            intVector.push_back((int)lua_tonumber(this->luaState, -1));
            lua_pop(this->luaState, 1);
        }
        unlua_clean();
        return intVector;
    }
    else{
        return vector<int>();
    }
    
}

vector<string> LuaScript::unlua_getTableKeys(const string& name_) {
    string code =
        "function getKeys(name_) "
        "s = \"\""
        "for k, v in pairs(_G[name_]) do "
        "    s = s..k..\",\" "
        "    end "
        "return s "
        "end"; // function for getting table keys

    luaL_loadstring(this->luaState, code.c_str()); // execute code
    lua_pcall(this->luaState, 0, 0, 0);
    lua_getglobal(this->luaState, "getKeys"); // get function
    lua_pushstring(this->luaState, name_.c_str());
    lua_pcall(this->luaState, 1 , 1, 0); // execute function

    const string test = lua_tostring(luaState, -1);
    vector<string> strings;
    string temp = "";

    Logger::log("TEMP: " + test);

    for(unsigned int i = 0; i < test.size(); i++) {
        if(test.at(i) != ',') {
            temp += test.at(i);
        }
        else {
            strings.push_back(temp);
            temp= "";
        }
    }
    unlua_clean();
    return strings;
}

bool LuaScript::unlua_getToStack(const string& variableName_) {
    this->level = 0;
    string var = "";
    for(unsigned int i = 0; i < variableName_.size(); i++) {
        if(variableName_.at(i) == '.') {
            if(this->level == 0) {
                lua_getglobal(this->luaState, var.c_str());
            }
            else {
                lua_getfield(this->luaState, -1, var.c_str());
            }

            if(lua_isnil(this->luaState, -1)) {
                Logger::error("Can't get " + variableName_ + ". " + var + " is not defined.");
                return false;
            }
            else {
                var = "";
                this->level++;
            }
        } else {
            var += variableName_.at(i);
        }
    }

    if(level == 0) {
        lua_getglobal(this->luaState, var.c_str());
    }
    else {
        lua_getfield(this->luaState, -1, var.c_str());
    }

    if(lua_isnil(luaState, -1)) {
        Logger::error("Can't get " + variableName_ + ". " + var + " is not defined.");
        return false;
    }

    return true;
}
