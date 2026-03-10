#include <lua.hpp>
#include <iostream>

int main()
{
    lua_State* pL = luaL_newstate();
    luaL_openlibs(pL);

    if (luaL_dofile(pL, "resources/sample.lua") != LUA_OK)  // FIXME
    {
        std::cout << "Failed to execute Lua: " << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return EXIT_FAILURE;
    }

    lua_close(pL);

    return EXIT_SUCCESS;
}
