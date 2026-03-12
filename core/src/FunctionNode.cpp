#include "FunctionNode.h"

namespace Add
{
    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        const Node value(NodeType::value, 0.f);
        const Node op(NodeType::add);

        UiNode ui_node;
        ui_node.type       = UiNodeType::add;
        ui_node.ui.add.lhs = graph.insert_node(value);
        ui_node.ui.add.rhs = graph.insert_node(value);
        ui_node.id         = graph.insert_node(op);

        graph.insert_edge(ui_node.id, ui_node.ui.add.lhs);
        graph.insert_edge(ui_node.id, ui_node.ui.add.rhs);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show()
    {
        // TODO
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.add.lhs);
        graph.erase_node(uiNode.ui.add.rhs);
    }
};  // namespace Add

std::vector<FunctionNode> FunctionNode::Get()
{
    return {
        {Add::Insert, Add::Show, Add::Erase},
    };
}