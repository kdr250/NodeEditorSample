#include "CppFunctions.h"
#include <iostream>
#include <lua.hpp>

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

void* CppFunctions::GetFunction(const std::string& functionName)
{
    if (functionName == "UltimateFunction")
    {
        return (void*)UltimateFunction;
    }
    else if (functionName == "UltimateFunction2")
    {
        return (void*)UltimateFunction2;
    }

    return nullptr;
}

std::vector<std::string> CppFunctions::GetFunctionNames()
{
    return {
        "UltimateFunction",
        "UltimateFunction2",
    };
}
