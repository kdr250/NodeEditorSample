#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include "Graph.h"
#include "Node.h"

using namespace example;

struct FunctionNode
{
    std::string mName;
    std::function<int(Graph<Node>&, std::vector<UiNode>&)> mInsertGraphFunction;
    std::function<void(Graph<Node>&, const UiNode&)> mShowFunction;
    std::function<void(Graph<Node>&, const UiNode&)> mEraseGraphFunction;

    static std::unordered_map<UiNodeType, FunctionNode> Get();
};
