#include "lua_runner.h"
#include <string>
#include <tuple>

extern "C" {

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <lj_ctype.h>

}

using std::string;
using std::tuple;

tuple<string,int> run(string const &script) {
  // Create the lua state.
  lua_State *L = luaL_newstate();
  if (L == NULL) {
    return std::make_tuple("luaL_newstate has failed", 1);
  }

  // Add in the lua standard libraries
  luaL_openlibs(L);

  //if (luaL_loadfile(L, "test.lua")) {
  if (luaL_dostring(L, script.c_str())) {
    return std::make_tuple(lua_tostring(L, -1), 1);
  }

  string res;
  if (lua_gettop(L) > 0) {
    res = lua_tostring(L, -1);
  } else {
    res = "no result";
  }

  lua_close(L);

  return std::make_tuple(res, 0);
}