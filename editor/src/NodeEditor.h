#pragma once

#include <imnodes.h>
#include <imgui.h>
#include <utility>
#include "Graph.h"

enum class NodeType
{
    add,
    multiply,
    sine,
    time,
    value,
    print,
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

    std::pair<const example::Graph<Node>, const int> getGraph() const;
    bool canEvaluate() const;

private:
    NodeEditor();
    NodeEditor(const NodeEditor&)            = delete;
    NodeEditor& operator=(const NodeEditor&) = delete;

    enum class UiNodeType
    {
        add,
        multiply,
        sine,
        time,
        print,
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
                int input;
            } sine;

            struct
            {
                int input;
            } print;
        } ui;
    };

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
