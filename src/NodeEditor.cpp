#include "NodeEditor.h"

#include <SDL3/SDL_timer.h>
#include <lua.hpp>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <vector>

static float current_time_seconds = 0.f;

namespace example
{
    void NodeEditorInitialize()
    {
        ImNodesIO& io                           = ImNodes::GetIO();
        io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
        NodeEditor::Instance();
    }

    void NodeEditorShow()
    {
        auto color_editor = NodeEditor::Instance();
        color_editor->show();
    }

    void NodeEditorShutdown() {}
}  // namespace example

NodeEditor::NodeEditor() :
    graph_(), nodes_(), root_node_id_(-1), minimap_location_(ImNodesMiniMapLocation_BottomRight)
{
}

NodeEditor* NodeEditor::Instance()
{
    static NodeEditor instance;
    return &instance;
}

void NodeEditor::show()
{
    // Update timer context
    current_time_seconds = 0.001f * SDL_GetTicks();

    auto flags = ImGuiWindowFlags_MenuBar;

    // The node editor window
    ImGui::Begin("color node editor", NULL, flags);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Mini-map"))
        {
            const char* names[] = {
                "Top Left",
                "Top Right",
                "Bottom Left",
                "Bottom Right",
            };
            int locations[] = {
                ImNodesMiniMapLocation_TopLeft,
                ImNodesMiniMapLocation_TopRight,
                ImNodesMiniMapLocation_BottomLeft,
                ImNodesMiniMapLocation_BottomRight,
            };

            for (int i = 0; i < 4; i++)
            {
                bool selected = minimap_location_ == locations[i];
                if (ImGui::MenuItem(names[i], NULL, &selected))
                    minimap_location_ = locations[i];
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Style"))
        {
            if (ImGui::MenuItem("Classic"))
            {
                ImGui::StyleColorsClassic();
                ImNodes::StyleColorsClassic();
            }
            if (ImGui::MenuItem("Dark"))
            {
                ImGui::StyleColorsDark();
                ImNodes::StyleColorsDark();
            }
            if (ImGui::MenuItem("Light"))
            {
                ImGui::StyleColorsLight();
                ImNodes::StyleColorsLight();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::TextUnformatted("Edit the color of the output color window using nodes.");
    ImGui::Columns(2);
    ImGui::TextUnformatted("A -- add node");
    ImGui::TextUnformatted("X -- delete selected node or link");
    ImGui::NextColumn();
    bool isEvaluatePressed = ImGui::Button("evaluate", ImVec2(80, 20));
    ImGui::Columns(1);

    ImNodes::BeginNodeEditor();

    // Handle new nodes
    // These are driven by the user, so we place this code before rendering the nodes
    {
        const bool open_popup = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)
                                && ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_A);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
        if (!ImGui::IsAnyItemHovered() && open_popup)
        {
            ImGui::OpenPopup("add node");
        }

        if (ImGui::BeginPopup("add node"))
        {
            const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

            if (ImGui::MenuItem("add"))
            {
                const Node value(NodeType::value, 0.f);
                const Node op(NodeType::add);

                UiNode ui_node;
                ui_node.type       = UiNodeType::add;
                ui_node.ui.add.lhs = graph_.insert_node(value);
                ui_node.ui.add.rhs = graph_.insert_node(value);
                ui_node.id         = graph_.insert_node(op);

                graph_.insert_edge(ui_node.id, ui_node.ui.add.lhs);
                graph_.insert_edge(ui_node.id, ui_node.ui.add.rhs);

                nodes_.push_back(ui_node);
                ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
            }

            if (ImGui::MenuItem("multiply"))
            {
                const Node value(NodeType::value, 0.f);
                const Node op(NodeType::multiply);

                UiNode ui_node;
                ui_node.type            = UiNodeType::multiply;
                ui_node.ui.multiply.lhs = graph_.insert_node(value);
                ui_node.ui.multiply.rhs = graph_.insert_node(value);
                ui_node.id              = graph_.insert_node(op);

                graph_.insert_edge(ui_node.id, ui_node.ui.multiply.lhs);
                graph_.insert_edge(ui_node.id, ui_node.ui.multiply.rhs);

                nodes_.push_back(ui_node);
                ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
            }

            if (ImGui::MenuItem("sine"))
            {
                const Node value(NodeType::value, 0.f);
                const Node op(NodeType::sine);

                UiNode ui_node;
                ui_node.type          = UiNodeType::sine;
                ui_node.ui.sine.input = graph_.insert_node(value);
                ui_node.id            = graph_.insert_node(op);

                graph_.insert_edge(ui_node.id, ui_node.ui.sine.input);

                nodes_.push_back(ui_node);
                ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
            }

            if (ImGui::MenuItem("time"))
            {
                UiNode ui_node;
                ui_node.type = UiNodeType::time;
                ui_node.id   = graph_.insert_node(Node(NodeType::time));

                nodes_.push_back(ui_node);
                ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
            }

            if (ImGui::MenuItem("print") && root_node_id_ == -1)
            {
                const Node value(NodeType::value, 0.f);
                const Node print(NodeType::print);

                UiNode ui_node;
                ui_node.type           = UiNodeType::print;
                ui_node.ui.print.input = graph_.insert_node(value);
                ui_node.id             = graph_.insert_node(print);

                graph_.insert_edge(ui_node.id, ui_node.ui.sine.input);

                nodes_.push_back(ui_node);
                ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                root_node_id_ = ui_node.id;
            }

            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
    }

    for (const UiNode& node : nodes_)
    {
        switch (node.type)
        {
            case UiNodeType::add:
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
                    if (graph_.num_edges_from_node(node.ui.add.lhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel", &graph_.node(node.ui.add.lhs).value, 0.01f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                {
                    ImNodes::BeginInputAttribute(node.ui.add.rhs);
                    const float label_width = ImGui::CalcTextSize("right").x;
                    ImGui::TextUnformatted("right");
                    if (graph_.num_edges_from_node(node.ui.add.rhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel", &graph_.node(node.ui.add.rhs).value, 0.01f);
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
            break;
            case UiNodeType::multiply:
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
                    if (graph_.num_edges_from_node(node.ui.multiply.lhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel",
                                         &graph_.node(node.ui.multiply.lhs).value,
                                         0.01f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                {
                    ImNodes::BeginInputAttribute(node.ui.multiply.rhs);
                    const float label_width = ImGui::CalcTextSize("right").x;
                    ImGui::TextUnformatted("right");
                    if (graph_.num_edges_from_node(node.ui.multiply.rhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel",
                                         &graph_.node(node.ui.multiply.rhs).value,
                                         0.01f);
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
            break;

            case UiNodeType::sine:
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
                    if (graph_.num_edges_from_node(node.ui.sine.input) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel",
                                         &graph_.node(node.ui.sine.input).value,
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
            break;
            case UiNodeType::time:
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
            break;

            case UiNodeType::print:
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
                    if (graph_.num_edges_from_node(node.ui.print.input) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel",
                                         &graph_.node(node.ui.print.input).value,
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
            break;
        }
    }

    for (const auto& edge : graph_.edges())
    {
        // If edge doesn't start at value, then it's an internal edge, i.e.
        // an edge which links a node's operation to its input. We don't
        // want to render node internals with visible links.
        if (graph_.node(edge.from).type != NodeType::value)
            continue;

        ImNodes::Link(edge.id, edge.from, edge.to);
    }

    ImNodes::MiniMap(0.2f, minimap_location_);
    ImNodes::EndNodeEditor();

    // Handle new links
    // These are driven by Imnodes, so we place the code after EndNodeEditor().

    {
        int start_attr, end_attr;
        if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
        {
            const NodeType start_type = graph_.node(start_attr).type;
            const NodeType end_type   = graph_.node(end_attr).type;

            const bool valid_link = start_type != end_type;
            if (valid_link)
            {
                // Ensure the edge is always directed from the value to
                // whatever produces the value
                if (start_type != NodeType::value)
                {
                    std::swap(start_attr, end_attr);
                }
                graph_.insert_edge(start_attr, end_attr);
            }
        }
    }

    // Handle deleted links

    {
        int link_id;
        if (ImNodes::IsLinkDestroyed(&link_id))
        {
            graph_.erase_edge(link_id);
        }
    }

    {
        const int num_selected = ImNodes::NumSelectedLinks();
        if (num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X))
        {
            static std::vector<int> selected_links;
            selected_links.resize(static_cast<size_t>(num_selected));
            ImNodes::GetSelectedLinks(selected_links.data());
            for (const int edge_id : selected_links)
            {
                graph_.erase_edge(edge_id);
            }
        }
    }

    {
        const int num_selected = ImNodes::NumSelectedNodes();
        if (num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X))
        {
            static std::vector<int> selected_nodes;
            selected_nodes.resize(static_cast<size_t>(num_selected));
            ImNodes::GetSelectedNodes(selected_nodes.data());
            for (const int node_id : selected_nodes)
            {
                graph_.erase_node(node_id);
                auto iter = std::find_if(nodes_.begin(),
                                         nodes_.end(),
                                         [node_id](const UiNode& node) -> bool
                                         {
                                             return node.id == node_id;
                                         });
                // Erase any additional internal nodes
                switch (iter->type)
                {
                    case UiNodeType::add:
                        graph_.erase_node(iter->ui.add.lhs);
                        graph_.erase_node(iter->ui.add.rhs);
                        break;
                    case UiNodeType::multiply:
                        graph_.erase_node(iter->ui.multiply.lhs);
                        graph_.erase_node(iter->ui.multiply.rhs);
                        break;
                    case UiNodeType::sine:
                        graph_.erase_node(iter->ui.sine.input);
                        break;
                    case UiNodeType::print:
                        graph_.erase_node(iter->ui.print.input);
                        break;
                    default:
                        break;
                }
                nodes_.erase(iter);
            }
        }
    }

    ImGui::End();

    // into Lua
    if (isEvaluatePressed && root_node_id_ != -1)
    {
        auto luaSource = evaluate(graph_, root_node_id_);
        executeLua(luaSource);
    }
}

std::stringstream NodeEditor::evaluate(const example::Graph<Node>& graph, const int root_node)
{
    std::cout << "###### Start evaluate ####" << std::endl;
    std::stringstream result;

    std::stack<int> postorder;
    dfs_traverse(graph,
                 root_node,
                 [&postorder](const int node_id) -> void
                 {
                     postorder.push(node_id);
                 });

    std::stack<float> value_stack;
    std::stack<std::string> code_stack;
    unsigned int variable_id = 0;
    while (!postorder.empty())
    {
        const int id = postorder.top();
        postorder.pop();
        const Node node = graph.node(id);

        switch (node.type)
        {
            case NodeType::add:
            {
                std::cout << "====NodeType::add====" << std::endl;
                const float rhs    = value_stack.top();
                std::string rhsStr = code_stack.top();
                std::cout << "rhs = " << rhs << std::endl;
                value_stack.pop();
                code_stack.pop();
                const float lhs    = value_stack.top();
                std::string lhsStr = code_stack.top();
                std::cout << "lhs = " << lhs << std::endl;
                value_stack.pop();
                code_stack.pop();
                value_stack.push(lhs + rhs);
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << lhsStr << " + " << rhsStr << ";" << std::endl;
                code_stack.push(varId);
                std::cout << "pushed result = " << (lhs + rhs) << std::endl;
            }
            break;
            case NodeType::multiply:
            {
                std::cout << "====NodeType::multiply====" << std::endl;
                const float rhs    = value_stack.top();
                std::string rhsStr = code_stack.top();
                std::cout << "rhs = " << rhs << std::endl;
                value_stack.pop();
                code_stack.pop();
                const float lhs    = value_stack.top();
                std::string lhsStr = code_stack.top();
                std::cout << "lhs = " << lhs << std::endl;
                value_stack.pop();
                code_stack.pop();
                value_stack.push(rhs * lhs);
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << lhsStr << " * " << rhsStr << ";" << std::endl;
                code_stack.push(varId);
                std::cout << "pushed result = " << (lhs + rhs) << std::endl;
            }
            break;
            case NodeType::sine:
            {
                std::cout << "====NodeType::sine====" << std::endl;
                const float x    = value_stack.top();
                std::string xStr = code_stack.top();
                std::cout << "x = " << x << std::endl;
                value_stack.pop();
                code_stack.pop();
                const float res = std::abs(std::sin(x));
                value_stack.push(res);
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << "math.sin(" << xStr << ");" << std::endl;
                code_stack.push(varId);
                std::cout << "pushed result = " << res << std::endl;
            }
            break;
            case NodeType::time:
            {
                std::cout << "====NodeType::time====" << std::endl;
                value_stack.push(current_time_seconds);
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << "os.clock();" << std::endl;
                code_stack.push(varId);
                std::cout << "pushed result = " << current_time_seconds << std::endl;
            }
            break;
            case NodeType::value:
            {
                // If the edge does not have an edge connecting to another node, then just use the value
                // at this node. It means the node's input pin has not been connected to anything and
                // the value comes from the node's UI.
                std::cout << "====NodeType::value====" << std::endl;
                if (graph.num_edges_from_node(id) == 0ull)
                {
                    value_stack.push(node.value);
                    code_stack.push(std::to_string(node.value));
                    std::cout << "pushed result node value = " << node.value << std::endl;
                }
            }
            break;
            case NodeType::print:
            {
                std::cout << "====NodeType::print====" << std::endl;
                std::string input = code_stack.top();
                code_stack.pop();
                result << "print(" << input << ");" << std::endl;
                std::cout << "↓↓↓↓ Lua ↓↓↓" << std::endl
                          << result.str() << "↑↑↑↑ Lua ↑↑↑" << std::endl;
            }
            break;
            default:
                break;
        }
    }

    std::cout << "###### End evaluate ####" << std::endl;

    return result;
}

void NodeEditor::executeLua(std::stringstream& luaSource)
{
    lua_State* pL = luaL_newstate();
    luaL_openlibs(pL);

    if (luaL_dostring(pL, luaSource.str().c_str()) != LUA_OK)
    {
        std::cerr << lua_tostring(pL, lua_gettop(pL)) << std::endl;
        lua_close(pL);
        return;
    }

    lua_close(pL);
}
