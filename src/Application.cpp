#include "Application.h"

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

        // ImGui_ImplSDL3_ProcessEvent(&event);
    }
}

void Application::Update()
{
    // TODO
}

void Application::GenerateOutput()
{
    // FIXME
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
    SDL_RenderLine(mRenderer, 100, 100, 500, 500);

    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderPoint(mRenderer, 300, 50);

    SDL_FRect rect {100.0f, 500.0f, 20.0f, 10.0f};
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderRect(mRenderer, &rect);

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
    // TODO
}

void Application::TerminateGUI()
{
    // TODO
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
