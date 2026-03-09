#pragma once

#include <imnodes.h>
#include <imgui.h>
#include "Graph.h"

enum class NodeType
{
    add,
    multiply,
    output,
    sine,
    time,
    value
};

struct Node
{
    NodeType type;
    float value;

    explicit Node(const NodeType t) : type(t), value(0.f) {}

    Node(const NodeType t, const float v) : type(t), value(v) {}
};

class NodeEditor
{
public:
    static NodeEditor* Instance();

    void show();

private:
    NodeEditor();
    NodeEditor(const NodeEditor&)            = delete;
    NodeEditor& operator=(const NodeEditor&) = delete;

    ImU32 evaluate(const example::Graph<Node>& graph, const int root_node);

    enum class UiNodeType
    {
        add,
        multiply,
        output,
        sine,
        time,
    };

    struct UiNode
    {
        UiNodeType type;
        // The identifying id of the ui node. For add, multiply, sine, and time
        // this is the "operation" node id. The additional input nodes are
        // stored in the structs.
        int id;

        union
        {
            struct
            {
                int lhs, rhs;
            } add;

            struct
            {
                int lhs, rhs;
            } multiply;

            struct
            {
                int r, g, b;
            } output;

            struct
            {
                int input;
            } sine;
        } ui;
    };

    example::Graph<Node> graph_;
    std::vector<UiNode> nodes_;
    int root_node_id_;
    ImNodesMiniMapLocation minimap_location_;

    ImU32 mResult = IM_COL32(255, 20, 147, 255);
};

namespace example
{
    void NodeEditorInitialize();
    void NodeEditorShow();
    void NodeEditorShutdown();
}  // namespace example
