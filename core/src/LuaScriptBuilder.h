#pragma once

#include <sstream>
#include "Graph.h"
#include "Node.h"

namespace LuaScriptBuilder
{
    std::stringstream Evaluate(const example::Graph<Node>& graph, const int root_node);

}  // namespace LuaScriptBuilder
