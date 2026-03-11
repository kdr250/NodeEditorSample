#pragma once

#include <sstream>
#include "Graph.h"
#include "NodeEditor.h"

namespace LuaScriptBuilder
{
    std::stringstream Evaluate(const example::Graph<Node>& graph, const int root_node);

    void SaveFile(std::stringstream& luaSource);

}  // namespace LuaScriptBuilder
