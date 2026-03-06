#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>

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

    void Shutdown();
    bool ShouldClose();

private:
    SDL_Window* mWindow     = nullptr;
    SDL_Renderer* mRenderer = nullptr;

    ImGuiContext* mGUIContext = nullptr;

    bool mIsRunning = true;
};
