#include <lua.hpp>
#include <iostream>

int main()
{
    lua_State* pL = luaL_newstate();
    luaL_openlibs(pL);

#ifdef __EMSCRIPTEN__
    const char* path = "resources/sample.lua";  // FIXME
#else
    const char* path = "resources/output.lua";
#endif
    if (luaL_dofile(pL, path) != LUA_OK)
    {
        std::cout << "Failed to execute Lua: " << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return EXIT_FAILURE;
    }

    lua_close(pL);

    return EXIT_SUCCESS;
}
