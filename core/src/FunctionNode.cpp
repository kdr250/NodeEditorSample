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
        Node execute(NodeType::execute);
        const Node value(NodeType::value, 0.f);
        const Node print(NodeType::print);

        UiNode ui_node;
        ui_node.type           = UiNodeType::print;
        ui_node.ui.print.input = graph.insert_node(value);
        ui_node.id             = graph.insert_node(print);

        execute.id               = ui_node.id;
        ui_node.ui.print.execute = graph.insert_node(execute);

        graph.insert_edge(ui_node.id, ui_node.ui.print.execute);
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
            ImNodes::BeginInputAttribute(node.ui.print.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.print.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

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
        graph.erase_node(uiNode.ui.print.execute);
        graph.erase_node(uiNode.ui.print.input);
    }
}  // namespace Print

namespace Time
{
    std::string Name()
    {
        return "time";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        UiNode ui_node;
        ui_node.type = UiNodeType::time;
        ui_node.id   = graph.insert_node(Node(NodeType::time));

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("time");
        ImNodes::EndNodeTitleBar();

        ImNodes::BeginOutputAttribute(node.id);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode) {}

}  // namespace Time

namespace Ultimate
{
    std::string Name()
    {
        return "ultimate";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node value(NodeType::value, 0.f);
        const Node op(NodeType::ultimate);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type = UiNodeType::ultimate;

        ui_node.ui.ultimate.input = graph.insert_node(value);
        ui_node.id                = graph.insert_node(op);

        execute.id                  = ui_node.id;
        ui_node.ui.ultimate.execute = graph.insert_node(execute);
        next.id                     = ui_node.id;
        ui_node.ui.ultimate.next    = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.ultimate.execute);
        graph.insert_edge(ui_node.id, ui_node.ui.ultimate.input);
        graph.insert_edge(ui_node.ui.ultimate.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("ultimate");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.ultimate.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.ultimate.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.ultimate.input);
            const float label_width = ImGui::CalcTextSize("number").x;
            ImGui::TextUnformatted("number");
            if (graph.num_edges_from_node(node.ui.ultimate.input) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel",
                                 &graph.node(node.ui.ultimate.input).value,
                                 0.01f,
                                 0.f,
                                 1.0f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.ultimate.next);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted(">");
            ImNodes::EndOutputAttribute();
        }

        {
            ImNodes::BeginOutputAttribute(node.id);
            const float label_width = ImGui::CalcTextSize("out").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted("out");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.ultimate.execute);
        graph.erase_node(uiNode.ui.ultimate.input);
        graph.erase_node(uiNode.ui.ultimate.next);
    }
}  // namespace Ultimate

namespace Ultimate2
{
    std::string Name()
    {
        return "ultimate2";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node value(NodeType::value, 0.f);
        const Node op(NodeType::ultimate2);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type               = UiNodeType::ultimate2;
        ui_node.ui.ultimate2.input = graph.insert_node(value);
        ui_node.id                 = graph.insert_node(op);

        execute.id                   = ui_node.id;
        ui_node.ui.ultimate2.execute = graph.insert_node(execute);

        next.id                   = ui_node.id;
        ui_node.ui.ultimate2.next = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.ultimate2.execute);
        graph.insert_edge(ui_node.id, ui_node.ui.ultimate2.input);
        graph.insert_edge(ui_node.ui.ultimate2.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("ultimate2");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.ultimate2.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.ultimate2.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.ultimate2.input);
            const float label_width = ImGui::CalcTextSize("number").x;
            ImGui::TextUnformatted("number");
            if (graph.num_edges_from_node(node.ui.ultimate2.input) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel",
                                 &graph.node(node.ui.ultimate2.input).value,
                                 0.01f,
                                 0.f,
                                 1.0f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.ultimate2.next);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted(">");
            ImNodes::EndOutputAttribute();
        }

        {
            ImNodes::BeginOutputAttribute(node.id);
            const float label_width = ImGui::CalcTextSize("out").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted("out");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.ultimate2.execute);
        graph.erase_node(uiNode.ui.ultimate2.input);
        graph.erase_node(uiNode.ui.ultimate2.next);
    }
}  // namespace Ultimate2

namespace If
{
    std::string Name()
    {
        return "if";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node value(NodeType::boolean, false);
        const Node op(NodeType::IF);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type        = UiNodeType::IF;
        ui_node.ui.If.input = graph.insert_node(value);
        ui_node.id          = graph.insert_node(op);

        execute.id            = ui_node.id;
        ui_node.ui.If.execute = graph.insert_node(execute);

        next.id            = ui_node.id;
        ui_node.ui.If.next = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.If.execute);
        graph.insert_edge(ui_node.id, ui_node.ui.If.input);
        graph.insert_edge(ui_node.ui.If.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("if");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.If.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.If.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.If.input);
            const float label_width = ImGui::CalcTextSize("condition").x;
            ImGui::TextUnformatted("condition");
            if (graph.num_edges_from_node(node.ui.If.input) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::Checkbox("##hidelabel", (bool*)&graph.node(node.ui.If.input).condition);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.If.next);
            const float label_width = ImGui::CalcTextSize("true >").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted("true >");
            ImNodes::EndOutputAttribute();
        }

        // // TODO: implement false
        // {
        //     ImNodes::BeginOutputAttribute(node.ui.ultimate2.next);
        //     const float label_width = ImGui::CalcTextSize("false").x;
        //     ImGui::Indent(node_width - label_width);
        //     ImGui::TextUnformatted("false");
        //     ImNodes::EndOutputAttribute();
        // }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.If.execute);
        graph.erase_node(uiNode.ui.If.input);
        graph.erase_node(uiNode.ui.If.next);
    }
}  // namespace If

namespace Else
{
    std::string Name()
    {
        return "else";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node op(NodeType::ELSE);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type = UiNodeType::ELSE;
        ui_node.id   = graph.insert_node(op);

        execute.id              = ui_node.id;
        ui_node.ui.Else.execute = graph.insert_node(execute);

        next.id              = ui_node.id;
        ui_node.ui.Else.next = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.Else.execute);
        graph.insert_edge(ui_node.ui.Else.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("else");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.EndIf.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.EndIf.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.EndIf.next);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted(">");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.Else.execute);
        graph.erase_node(uiNode.ui.Else.next);
    }
}  // namespace Else

namespace EndIf
{
    std::string Name()
    {
        return "endif";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node op(NodeType::END_IF);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type = UiNodeType::END_IF;
        ui_node.id   = graph.insert_node(op);

        execute.id               = ui_node.id;
        ui_node.ui.EndIf.execute = graph.insert_node(execute);

        next.id               = ui_node.id;
        ui_node.ui.EndIf.next = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.EndIf.execute);
        graph.insert_edge(ui_node.ui.EndIf.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("endif");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.EndIf.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.EndIf.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.EndIf.next);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted(">");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.EndIf.execute);
        graph.erase_node(uiNode.ui.EndIf.next);
    }
}  // namespace EndIf

namespace Less
{
    std::string Name()
    {
        return "<";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        const Node value(NodeType::value, 0.0f);
        const Node op(NodeType::less, false);

        UiNode ui_node;
        ui_node.type        = UiNodeType::less;
        ui_node.ui.less.lhs = graph.insert_node(value);
        ui_node.ui.less.rhs = graph.insert_node(value);
        ui_node.id          = graph.insert_node(op);

        graph.insert_edge(ui_node.id, ui_node.ui.less.lhs);
        graph.insert_edge(ui_node.id, ui_node.ui.less.rhs);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("<");
        ImNodes::EndNodeTitleBar();
        {
            ImNodes::BeginInputAttribute(node.ui.less.lhs);
            const float label_width = ImGui::CalcTextSize("left").x;
            ImGui::TextUnformatted("left");
            if (graph.num_edges_from_node(node.ui.less.lhs) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel", &graph.node(node.ui.less.lhs).value, 0.01f);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.less.rhs);
            const float label_width = ImGui::CalcTextSize("right").x;
            ImGui::TextUnformatted("right");
            if (graph.num_edges_from_node(node.ui.less.rhs) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::DragFloat("##hidelabel", &graph.node(node.ui.less.rhs).value, 0.01f);
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
        graph.erase_node(uiNode.ui.less.lhs);
        graph.erase_node(uiNode.ui.less.rhs);
    }
};  // namespace Less

namespace Loop
{
    std::string Name()
    {
        return "loop";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node count(NodeType::integer, 1);
        const Node op(NodeType::LOOP);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type          = UiNodeType::LOOP;
        ui_node.ui.Loop.count = graph.insert_node(count);
        ui_node.id            = graph.insert_node(op);

        execute.id              = ui_node.id;
        ui_node.ui.Loop.execute = graph.insert_node(execute);

        next.id              = ui_node.id;
        ui_node.ui.Loop.next = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.Loop.execute);
        graph.insert_edge(ui_node.id, ui_node.ui.Loop.count);
        graph.insert_edge(ui_node.ui.Loop.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("loop");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.If.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.If.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        {
            ImNodes::BeginInputAttribute(node.ui.Loop.count);
            const float label_width = ImGui::CalcTextSize("count").x;
            ImGui::TextUnformatted("count");
            if (graph.num_edges_from_node(node.ui.If.input) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::InputInt("##hidelabel", &graph.node(node.ui.Loop.count).integer);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.Loop.next);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted(">");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.Loop.execute);
        graph.erase_node(uiNode.ui.Loop.count);
        graph.erase_node(uiNode.ui.Loop.next);
    }
}  // namespace Loop

namespace EndLoop
{
    std::string Name()
    {
        return "endloop";
    };

    int Insert(Graph<Node>& graph, std::vector<UiNode>& nodes)
    {
        Node execute(NodeType::execute);
        const Node op(NodeType::END_LOOP, 0);
        Node next(NodeType::next);

        UiNode ui_node;
        ui_node.type = UiNodeType::END_LOOP;
        ui_node.id   = graph.insert_node(op);

        execute.id                 = ui_node.id;
        ui_node.ui.EndLoop.execute = graph.insert_node(execute);

        next.id                 = ui_node.id;
        ui_node.ui.EndLoop.next = graph.insert_node(next);

        graph.insert_edge(ui_node.id, ui_node.ui.EndLoop.execute);
        graph.insert_edge(ui_node.ui.EndLoop.next, ui_node.id);

        nodes.push_back(ui_node);
        return ui_node.id;
    }

    void Show(Graph<Node>& graph, const UiNode& node)
    {
        const float node_width = 100.0f;
        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("endloop");
        ImNodes::EndNodeTitleBar();

        {
            ImNodes::BeginInputAttribute(node.ui.EndLoop.execute);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::TextUnformatted(">");
            if (graph.num_edges_from_node(node.ui.EndLoop.execute) == 0ull)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(node_width - label_width);
                ImGui::PopItemWidth();
            }
            ImNodes::EndInputAttribute();
        }

        ImGui::Spacing();

        {
            ImNodes::BeginOutputAttribute(node.ui.EndLoop.next);
            const float label_width = ImGui::CalcTextSize(">").x;
            ImGui::Indent(node_width - label_width);
            ImGui::TextUnformatted(">");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    void Erase(Graph<Node>& graph, const UiNode& uiNode)
    {
        graph.erase_node(uiNode.ui.EndLoop.execute);
        graph.erase_node(uiNode.ui.EndLoop.next);
    }
}  // namespace EndLoop

std::unordered_map<UiNodeType, FunctionNode> FunctionNode::Get()
{
    // clang-format off
    return {
        {UiNodeType::add, {Add::Name(), Add::Insert, Add::Show, Add::Erase}},
        {UiNodeType::multiply, {Multiply::Name(), Multiply::Insert, Multiply::Show, Multiply::Erase}},
        {UiNodeType::sine, {Sine::Name(), Sine::Insert, Sine::Show, Sine::Erase}},
        {UiNodeType::time, {Time::Name(), Time::Insert, Time::Show, Time::Erase}},
        {UiNodeType::ultimate, {Ultimate::Name(), Ultimate::Insert, Ultimate::Show, Ultimate::Erase}},
        {UiNodeType::ultimate2, {Ultimate2::Name(), Ultimate2::Insert, Ultimate2::Show, Ultimate2::Erase}},
        {UiNodeType::print, {Print::Name(), Print::Insert, Print::Show, Print::Erase, true}},
        {UiNodeType::IF, {If::Name(), If::Insert, If::Show, If::Erase}},
        {UiNodeType::ELSE, {Else::Name(), Else::Insert, Else::Show, Else::Erase}},
        {UiNodeType::END_IF, {EndIf::Name(), EndIf::Insert, EndIf::Show, If::Erase}},
        {UiNodeType::less, {Less::Name(), Less::Insert, Less::Show, Less::Erase}},
        {UiNodeType::LOOP, {Loop::Name(), Loop::Insert, Loop::Show, Loop::Erase}},
        {UiNodeType::END_LOOP, {EndLoop::Name(), EndLoop::Insert, EndLoop::Show, EndLoop::Erase}},
    };
    // clang-format on
}
