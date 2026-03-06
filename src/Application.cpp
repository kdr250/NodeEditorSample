#include "Application.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <cassert>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif

namespace ed = ax::NodeEditor;

Application::Application() {}

bool Application::Initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("NodeEditorSample", 1024, 768, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    SDL_SetWindowResizable(mWindow, false);

    mRenderer = SDL_CreateRenderer(mWindow, NULL);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }
    SDL_SetRenderVSync(mRenderer, 1);

    InitializeGUI();

    return true;
}

void Application::RunLoop()
{
#ifdef __EMSCRIPTEN__
    auto callback = [](void* arg)
    {
        Application* pApp = reinterpret_cast<Application*>(arg);
        if (pApp->ShouldClose())
        {
            emscripten_cancel_main_loop();
            pApp->Shutdown();
            return;
        }
        pApp->Loop();
    };
    emscripten_set_main_loop_arg(callback, this, 0, true);
#else
    while (!ShouldClose())
    {
        Loop();
    }
    Shutdown();
#endif
}

void Application::Loop()
{
    ProcessInput();
    Update();
    GenerateOutput();
}

void Application::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                mIsRunning = false;
                break;

            case SDL_EVENT_MOUSE_MOTION:
                OnMouseMove();
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                OnScroll(event);
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                OnMouseButton(event);
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                OnKeyAction(event);
                break;

            default:
                break;
        }

        ProcessEventGUI(event);
    }
}

void Application::Update()
{
    UpdateGUI();
}

void Application::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    RenderGUI();
    SDL_RenderPresent(mRenderer);
}

void Application::OnMouseMove()
{
    // TODO
}

void Application::OnMouseButton(SDL_Event& event)
{
    // TODO
}

void Application::OnScroll(SDL_Event& event)
{
    // TODO
}

void Application::OnKeyAction(SDL_Event& event)
{
    assert(event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP);

    int key     = event.key.scancode;
    bool down   = event.key.down;
    bool repeat = event.key.repeat;

    if (down && key == SDL_SCANCODE_ESCAPE)
    {
        mIsRunning = false;
        return;
    }
}

void Application::InitializeGUI()
{
    mGUIContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(mGUIContext);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io    = ImGui::GetIO();
    io.IniFilename = "resources/gui/sample.ini";
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    RecreateFontAtlas();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(mWindow, mRenderer);
    ImGui_ImplSDLRenderer3_Init(mRenderer);

    // Editor
    ed::Config config;
    config.SettingsFile = "resources/gui/simple.json";
    mEditorContext      = ed::CreateEditor(&config);
}

void Application::ProcessEventGUI(SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void Application::UpdateGUI()
{
    ImGuiIO& io = ImGui::GetIO();

    // FIXME
    const float windowScale      = 1.0f;
    const float framebufferScale = 1.0f;

    if (io.WantSetMousePos)
    {
        io.MousePos.x *= windowScale;
        io.MousePos.y *= windowScale;
    }

    // Don't touch "uninitialized" mouse position
    if (io.MousePos.x > -FLT_MAX && io.MousePos.y > -FLT_MAX)
    {
        io.MousePos.x /= windowScale;
        io.MousePos.y /= windowScale;
    }
    io.DisplaySize.x /= windowScale;
    io.DisplaySize.y /= windowScale;

    io.DisplayFramebufferScale.x = framebufferScale;
    io.DisplayFramebufferScale.y = framebufferScale;

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    const auto windowBorderSize = ImGui::GetStyle().WindowBorderSize;
    const auto windowRounding   = ImGui::GetStyle().WindowRounding;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin("Content", nullptr, GetWindowFlags());
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, windowBorderSize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, windowRounding);

    // Node editor
    ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

    ImGui::Separator();

    ed::SetCurrentEditor(mEditorContext);
    ed::Begin("My Editor", ImVec2(0.0, 0.0f));
    int uniqueId = 1;
    // Start drawing nodes.
    ed::BeginNode(uniqueId++);
    ImGui::Text("Node A");
    ed::BeginPin(uniqueId++, ed::PinKind::Input);
    ImGui::Text("-> In");
    ed::EndPin();
    ImGui::SameLine();
    ed::BeginPin(uniqueId++, ed::PinKind::Output);
    ImGui::Text("Out ->");
    ed::EndPin();
    ed::EndNode();
    ed::End();
    ed::SetCurrentEditor(nullptr);

    ImGui::PopStyleVar(2);
    ImGui::End();
    ImGui::PopStyleVar(2);
}

void Application::RenderGUI()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void Application::TerminateGUI()
{
    ed::DestroyEditor(mEditorContext);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext(mGUIContext);
}

void Application::RecreateFontAtlas()
{
    ImGuiIO& io = ImGui::GetIO();

    IM_DELETE(io.Fonts);

    io.Fonts = IM_NEW(ImFontAtlas);

    ImFontConfig config;
    config.OversampleH = 4;
    config.OversampleV = 4;
    config.PixelSnapH  = false;

    io.Fonts->AddFontFromFileTTF("resources/data/Play-Regular.ttf", 18.0f, &config);
    io.Fonts->AddFontFromFileTTF("resources/data/Cuprum-Bold.ttf", 20.0f, &config);

    io.Fonts->Build();
}

ImGuiWindowFlags Application::GetWindowFlags() const
{
    return ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
           | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
           | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void Application::Shutdown()
{
    TerminateGUI();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool Application::ShouldClose()
{
    return !mIsRunning;
}
