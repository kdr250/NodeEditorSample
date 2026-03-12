#pragma once

#include <imnodes.h>
#include <imgui.h>
#include <utility>
#include <Node.h>
#include "Graph.h"

class NodeEditor
{
public:
    static NodeEditor* Instance();

    void show();

    std::pair<const example::Graph<Node>, const int> getGraph() const;
    bool canEvaluate() const;

    void saveFile(std::stringstream& luaSource);

private:
    NodeEditor();
    NodeEditor(const NodeEditor&)            = delete;
    NodeEditor& operator=(const NodeEditor&) = delete;

    example::Graph<Node> graph_;
    std::vector<UiNode> nodes_;
    int root_node_id_;
    ImNodesMiniMapLocation minimap_location_;

    bool isSavePressed = false;
};

namespace example
{
    void NodeEditorInitialize();
    void NodeEditorShow();
    void NodeEditorShutdown();
}  // namespace example
