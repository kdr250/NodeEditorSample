#pragma once

#include <functional>
#include "Graph.h"
#include "Node.h"

using namespace example;

struct FunctionNode
{
    std::function<int(Graph<Node>&, std::vector<UiNode>&)> mInsertGraphFunction;
    std::function<void()> mShowFunction;
    std::function<void(Graph<Node>&, const UiNode&)> mEraseGraphFunction;

    static std::vector<FunctionNode> Get();
};
