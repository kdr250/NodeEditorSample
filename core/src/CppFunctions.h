#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

struct lua_State;
using lua_CFunction = int (*)(lua_State* L);

int UltimateFunction(lua_State* pL);

struct CppFunctions
{
    static lua_CFunction GetFunction(const std::string& functionName)
    {
        // std::unordered_map<std::string, lua_CFunction> hoge;
        // hoge.emplace("UltimateFunction", UltimateFunction);

        if (functionName == "UltimateFunction")
        {
            return UltimateFunction;
        }
    }
};
