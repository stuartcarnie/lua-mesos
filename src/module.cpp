#include "module.h"
#include <mesos/executor.hpp>

#if LUA_VERSION_NUM < 502
#define luaL_newlib(L, l) ( lua_newtable( L ), luaL_register( L, NULL, l ) )
#endif

static int w__tostring(lua_State * L)
{
    lua_pushvalue(L, lua_upvalueindex(1));
    return 1;
}

int luaX_register_type(lua_State * L, const char * tname, const luaL_Reg * f)
{
    luaL_newmetatable(L, tname);

    // m.__index = m
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    // Add tostring function.
    lua_pushstring(L, tname);
    lua_pushcclosure(L, w__tostring, 1);
    lua_setfield(L, -2, "__tostring");


    if(f != nullptr) {
        luaL_register(L, 0, f);
    }

    lua_pop(L, 1); // Pops metatable.
    return 0;
}

static const struct luaL_Reg test_fns[] = {
        {nullptr, nullptr}
};

int luaopen_test(lua_State * L) {
    fprintf(stderr, "register Test\n");

    return luaX_register_type(L, "Test", nullptr);
};

int lua_newTest(lua_State * L) {

    return 1;
}

static const lua_CFunction types[] = {
        luaopen_test,
        nullptr,
};

static const luaL_Reg module[] = {
        { "Test", lua_newTest }
};


extern "C" int luaopen_mesos(lua_State * const L) {
    fprintf(stderr, "opening mesos\n");

    lua_newtable(L);

    for (const lua_CFunction* t = types; *t != nullptr; t++) {
        (*t)(L);
    }

    fprintf(stderr, "opened mesos\n");

    return 1;
}