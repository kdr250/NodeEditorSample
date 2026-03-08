#include "Application.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imnodes.h>
#include <cassert>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif

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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImNodes::CreateContext();
    ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f));

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(mWindow, mRenderer);
    ImGui_ImplSDLRenderer3_Init(mRenderer);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImNodes::StyleColorsDark();
}

void Application::ProcessEventGUI(SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void Application::UpdateGUI()
{
    ImGuiIO& io = ImGui::GetIO();

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Editor
    ImGui::Begin("simple node editor");

    ImNodes::BeginNodeEditor();
    ImNodes::BeginNode(1);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("simple node :)");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(2);
    ImGui::Text("input");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(3);
    ImGui::Indent(40);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
    ImNodes::EndNodeEditor();

    ImGui::End();
}

void Application::RenderGUI()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void Application::TerminateGUI()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
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
