#pragma once

#include <string>
#include <vector>

namespace CppFunctions
{
    void* GetFunction(const std::string& functionName);

    std::vector<std::string> GetFunctionNames();

};  // namespace CppFunctions
