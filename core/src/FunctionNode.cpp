#include "FunctionNode.h"

#include <imgui.h>
#include <imnodes.h>

namespace Add
{
    std::string Name()
    {
        return "add";
    };

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

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("add");
        ImNodes::EndNodeTitleBar();
        {
            ImNodes::BeginInputAttribute(node.ui.add.lhs);
            const float label_width = ImGui::CalcTextSize("left").x;
            ImGui::TextUnformatted("left");
            if (graph.num_edges_from_node(node.ui.add.lhs) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel", &graph.node(node.ui.add.lhs).value, 0.01f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.add.rhs);
            const float label_width = ImGui::CalcTextSize("right").x;
            ImGui::TextUnformatted("right");
            if (graph.num_edges_from_node(node.ui.add.rhs) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel", &graph.node(node.ui.add.rhs).value, 0.01f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.id);
            const float label_width = ImGui::CalcTextSize("result").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted("result");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.add.lhs);
        graph.erase_node(uiNode.ui.add.rhs);
    }
};  // namespace Add

namespace Multiply
{
    std::string Name()
    {
        return "multiply";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        const Node value(NodeType::value, 0.f);
        const Node op(NodeType::multiply);

        UiNode ui_node;
        ui_node.type            = UiNodeType::multiply;
        ui_node.ui.multiply.lhs = graph.insert_node(value);
        ui_node.ui.multiply.rhs = graph.insert_node(value);
        ui_node.id              = graph.insert_node(op);

        graph.insert_edge(ui_node.id, ui_node.ui.multiply.lhs);
        graph.insert_edge(ui_node.id, ui_node.ui.multiply.rhs);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("multiply");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.multiply.lhs);
            const float label_width = ImGui::CalcTextSize("left").x;
            ImGui::TextUnformatted("left");
            if (graph.num_edges_from_node(node.ui.multiply.lhs) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel", &graph.node(node.ui.multiply.lhs).value, 0.01f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.multiply.rhs);
            const float label_width = ImGui::CalcTextSize("right").x;
            ImGui::TextUnformatted("right");
            if (graph.num_edges_from_node(node.ui.multiply.rhs) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel", &graph.node(node.ui.multiply.rhs).value, 0.01f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.id);
            const float label_width = ImGui::CalcTextSize("result").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted("result");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.multiply.lhs);
        graph.erase_node(uiNode.ui.multiply.rhs);
    }
}  // namespace Multiply

namespace Sine
{
    std::string Name()
    {
        return "sine";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        const Node value(NodeType::value, 0.f);
        const Node op(NodeType::sine);

        UiNode ui_node;
        ui_node.type          = UiNodeType::sine;
        ui_node.ui.sine.input = graph.insert_node(value);
        ui_node.id            = graph.insert_node(op);

        graph.insert_edge(ui_node.id, ui_node.ui.sine.input);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("sine");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.sine.input);
            const float label_width = ImGui::CalcTextSize("number").x;
            ImGui::TextUnformatted("number");
            if (graph.num_edges_from_node(node.ui.sine.input) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel",
                                 &graph.node(node.ui.sine.input).value,
                                 0.01f,
                                 0.f,
                                 1.0f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.id);
            const float label_width = ImGui::CalcTextSize("output").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted("output");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.sine.input);
    }
}  // namespace Sine

namespace Print
{
    std::string Name()
    {
        return "print";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        const Node value(NodeType::value, 0.f);
        const Node print(NodeType::print);

        UiNode ui_node;
        ui_node.type           = UiNodeType::print;
        ui_node.ui.print.input = graph.insert_node(value);
        ui_node.id             = graph.insert_node(print);

        graph.insert_edge(ui_node.id, ui_node.ui.print.input);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(11, 109, 191, 255));
        ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, IM_COL32(45, 126, 194, 255));
        ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(81, 148, 204, 255));
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("print");
        ImNodes::EndNodeTitleBar();

        ImGui::Dummy(ImVec2(node_width, 0.f));
        {
            ImNodes::BeginInputAttribute(node.ui.print.input);
            const float label_width = ImGui::CalcTextSize("input").x;
            ImGui::TextUnformatted("input");
            if (graph.num_edges_from_node(node.ui.print.input) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel",
                                 &graph.node(node.ui.print.input).value,
                                 0.01f,
                                 0.f,
                                 1.0f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImNodes::EndNode();
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.print.input);
    }
}  // namespace Print

namespace Hoge
{
    std::string Name()
    {
        return "hoge";
    };
    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes) {}
    void Show(Graph<Node>& graph, const UiNode& node) {}
    void Erase(Graph<Node>& graph, const UiNode& uiNode) {}
}  // namespace Hoge

std::unordered_map<UiNodeType, FunctionNode> FunctionNode::Get()
{
    // clang-format off
    return {
        {UiNodeType::add, {Add::Name(), Add::Insert, Add::Show, Add::Erase}},
        {UiNodeType::multiply, {Multiply::Name(), Multiply::Insert, Multiply::Show, Multiply::Erase}},
        {UiNodeType::sine, {Sine::Name(), Sine::Insert, Sine::Show, Sine::Erase}},
        {UiNodeType::print, {Print::Name(), Print::Insert, Print::Show, Print::Erase, true}},
    };
    // clang-format on
}
