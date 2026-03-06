#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui-node-editor/imgui_node_editor.h>

namespace ed = ax::NodeEditor;

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

    bool mIsRunning = true;
};
