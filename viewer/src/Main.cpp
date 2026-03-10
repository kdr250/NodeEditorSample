#include <lua.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif

int main(int argc, char* argv[])
{
#ifdef __EMSCRIPTEN__
    // EM_ASM(FS.mount(IDBFS, {autoPersist : true}, "/resources"););
    // clang-format off
        EM_ASM(
            FS.mount(IDBFS, {}, '/resources');
            FS.syncfs(function (err) {
              assert(!err);
            });
        );
    // clang-format on
#endif

    lua_State* pL = luaL_newstate();
    luaL_openlibs(pL);

    auto file = fopen("/resources/output.lua", "r");
    if (!file)
    {
        std::cout << "file does not exist" << std::endl;
        return EXIT_FAILURE;
    }
    char str[256] = {};
    fread(&str[0], sizeof(*str), sizeof(str) / sizeof(*str), file);

    fclose(file);

    if (luaL_dostring(pL, str) != LUA_OK)
    {
        std::cout << "Failed to execute Lua: " << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return EXIT_FAILURE;
    }

    lua_close(pL);

    return EXIT_SUCCESS;
}
