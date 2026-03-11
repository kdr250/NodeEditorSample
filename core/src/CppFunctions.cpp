#include "CppFunctions.h"
#include <iostream>
#include <ranges>

int UltimateFunction(lua_State* pL)
{
    // Retrieve arguments from Lua
    const lua_Number num = lua_tonumber(pL, 1);
    lua_pop(pL, lua_gettop(pL));

    // Set return value to Lua
    lua_pushnumber(pL, num);

    std::cout << "C++ Ultimate Function! input value: " << num << std::endl;

    return 1;
}

int UltimateFunction2(lua_State* pL)
{
    // Retrieve arguments from Lua
    const lua_Number num = lua_tonumber(pL, 1);
    lua_pop(pL, lua_gettop(pL));

    // Set return value to Lua
    const int result = static_cast<int>(num) * 2;
    lua_pushnumber(pL, result);

    std::cout << "C++ Ultimate Function 2! input: " << num << ", output: " << result << std::endl;

    return 1;
}

std::vector<std::string> CppFunctions::GetFunctionNames()
{
    auto map      = GetFunctions();
    auto keysView = map | std::views::keys;
    std::vector<std::string> keys(keysView.begin(), keysView.end());
    return keys;
}

std::unordered_map<std::string, lua_CFunction> CppFunctions::GetFunctions()
{
    return {
        {"UltimateFunction", UltimateFunction},
        {"UltimateFunction2", UltimateFunction2},
    };
}
