#pragma once

#include <lua.hpp>
#include <string>
#include <vector>
#include <unordered_map>

namespace CppFunctions
{
    std::vector<std::string> GetFunctionNames();

    std::unordered_map<std::string, lua_CFunction> GetFunctions();

};  // namespace CppFunctions
