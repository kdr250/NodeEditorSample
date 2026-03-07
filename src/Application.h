#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui-node-editor/imgui_node_editor.h>

namespace ed = ax::NodeEditor;

/**
 * Struct to hold basic information about connection between
 * pins. Note that connection (aka. link) has its own ID.
 * This is useful later with dealing with selections, deletion
 * or other operations.
 */
struct LinkInfo
{
    ed::LinkId Id;
    ed::PinId InputId;
    ed::PinId OutputId;
};

class Application
{
public:
    Application();

    bool Initialize();
    void RunLoop();

private:
    void Loop();

    void ProcessInput();
    void Update();
    void GenerateOutput();

    // Mouse events
    void OnMouseMove();
    void OnMouseButton(SDL_Event& event);
    void OnScroll(SDL_Event& event);
    void OnKeyAction(SDL_Event& event);

    // GUI
    void InitializeGUI();
    void ProcessEventGUI(SDL_Event& event);
    void UpdateGUI();
    void RenderGUI();
    void TerminateGUI();

    void RecreateFontAtlas();
    ImGuiWindowFlags GetWindowFlags() const;

    void Shutdown();
    bool ShouldClose();

private:
    SDL_Window* mWindow     = nullptr;
    SDL_Renderer* mRenderer = nullptr;

    ImGuiContext* mGUIContext         = nullptr;
    ed::EditorContext* mEditorContext = nullptr;

    // Flag set for first frame only, some action need to be executed once.
    bool m_FirstFrame = true;
    // List of live links. It is dynamic unless you want to create read-only view over nodes.
    ImVector<LinkInfo> m_Links;
    // Counter to help generate link ids. In real application this will probably based on pointer to user data structure.
    int m_NextLinkId = 100;

    bool mIsRunning = true;
};
