#include "CppFunctions.h"
#include <iostream>
#include <ranges>

int UltimateFunction(lua_State* pL)
{
    // Retrieve arguments from Lua
    const lua_Number num = lua_tonumber(pL, 1);
    lua_pop(pL, lua_gettop(pL));

    std::cout << "C++ Ultimate Function! input : " << num << std::endl;

    return 0;
}

int UltimateFunction2(lua_State* pL)
{
    // Retrieve arguments from Lua
    const lua_Number num = lua_tonumber(pL, 1);
    lua_pop(pL, lua_gettop(pL));

    const float result = static_cast<float>(num) * 2;

    std::cout << "C++ Ultimate Function 2! input: " << num << ", x2 = " << result << std::endl;

    return 0;
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
