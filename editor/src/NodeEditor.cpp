#include "NodeEditor.h"

#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <FunctionNode.h>
#include "LuaScriptBuilder.h"

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif

static float current_time_seconds = 0.f;

namespace example
{
    void NodeEditorInitialize()
    {
#ifdef __EMSCRIPTEN__
        // clang-format off
        EM_ASM(
            FS.mkdir('/resources');
            FS.mount(IDBFS, {autoPersist: true}, '/resources');
            FS.syncfs(true, function (err) {
              assert(!err);
            });
        );
        // clang-format on
#endif

        ImNodesIO& io                           = ImNodes::GetIO();
        io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
        NodeEditor::Instance();
    }

    void NodeEditorShow()
    {
        auto color_editor = NodeEditor::Instance();
        color_editor->show();

        if (color_editor->canEvaluate())
        {
            auto [graph, rootId]     = color_editor->getGraph();
            std::stringstream source = LuaScriptBuilder::Evaluate(graph, rootId);
            color_editor->saveFile(source);
        }
    }

    void NodeEditorShutdown() {}
}  // namespace example

NodeEditor::NodeEditor() :
    graph_(), nodes_(), root_node_id_(-1), minimap_location_(ImNodesMiniMapLocation_BottomRight)
{
}

void NodeEditor::saveFile(std::stringstream& luaSource)
{
    std::ofstream file("resources/output.lua");
    file << luaSource.str();
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
    isSavePressed = ImGui::Button("Save", ImVec2(80, 20));
    ImGui::Columns(1);

    ImNodes::BeginNodeEditor();

    auto functionNodes = FunctionNode::Get();

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

            for (auto& [_, functionNode] : functionNodes)
            {
                if (ImGui::MenuItem(functionNode.mName.c_str()))
                {
                    if (functionNode.mIsRootNode && root_node_id_ != -1)
                    {
                        continue;
                    }

                    auto ui_node_id = functionNode.mInsertGraphFunction(graph_, nodes_);
                    ImNodes::SetNodeScreenSpacePos(ui_node_id, click_pos);

                    if (functionNode.mIsRootNode)
                    {
                        root_node_id_ = ui_node_id;
                    }
                }
            }

            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
    }

    for (const UiNode& node : nodes_)
    {
        auto functionNode = functionNodes[node.type];
        functionNode.mShowFunction(graph_, node);
    }

    for (const auto& edge : graph_.edges())
    {
        // If edge doesn't start at value, then it's an internal edge, i.e.
        // an edge which links a node's operation to its input. We don't
        // want to render node internals with visible links.
        if (graph_.node(edge.from).type != NodeType::value
            && graph_.node(edge.from).type != NodeType::boolean
            && graph_.node(edge.from).type != NodeType::execute)
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
            auto& start_node = graph_.node(start_attr);
            auto& end_node   = graph_.node(end_attr);

            const NodeType start_type = start_node.type;
            const NodeType end_type   = end_node.type;

            const PinType start_pin_type = Node::GetPinType(start_type);
            const PinType end_pin_type   = Node::GetPinType(end_type);

            const bool valid_link = (start_type != end_type) && (start_pin_type == end_pin_type);
            if (valid_link)
            {
                // Ensure the edge is always directed from the value to
                // whatever produces the value
                if (start_type != NodeType::value && start_type != NodeType::boolean
                    && start_type != NodeType::execute)
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
                auto functionNode = functionNodes[iter->type];
                functionNode.mEraseGraphFunction(graph_, *iter);

                nodes_.erase(iter);
            }
        }
    }

    ImGui::End();
}

std::pair<const example::Graph<Node>, const int> NodeEditor::getGraph() const
{
    return std::make_pair(graph_, root_node_id_);
}

bool NodeEditor::canEvaluate() const
{
    return isSavePressed && root_node_id_ != -1;
}
