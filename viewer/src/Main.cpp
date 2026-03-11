#include <lua.hpp>
#include <iostream>
#include <CppFunctions.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>

extern "C"
{
    static bool isSyncFinished = false;

    void EMSCRIPTEN_KEEPALIVE onSyncFinished()
    {
        isSyncFinished = true;
    }
}
#endif

int main()
{
#ifdef __EMSCRIPTEN__
    isSyncFinished = false;

    // clang-format off
    EM_ASM(
        FS.mkdir('/resources');
        FS.mount(IDBFS, {}, '/resources');
        FS.syncfs(true, function (err) {
            ccall('onSyncFinished', null, [], []);
        });
    );
    // clang-format on

    while (!isSyncFinished)
    {
        emscripten_sleep(1);
    }
#endif

    lua_State* pL = luaL_newstate();
    luaL_openlibs(pL);

    const char* path = "resources/output.lua";

    const char* script = R"(
        var0 = 1 + 2;
        print(var0);
        UltimateFunction();
    )";

    auto func = CppFunctions::GetFunction("UltimateFunction");

    lua_register(pL, "UltimateFunction", func);

    if (luaL_dostring(pL, script) != LUA_OK)
    {
        std::cout << "Failed to execute Lua: " << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return EXIT_FAILURE;
    }

    lua_close(pL);

    return EXIT_SUCCESS;
}
