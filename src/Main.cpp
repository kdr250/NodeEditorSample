#include <SDL3/SDL.h>

int main(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    auto window = SDL_CreateWindow("NodeEditorSample", 1024, 768, 0);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    auto renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                {
                    isRunning = false;
                    break;
                }

                default:
                    break;
            }
        }

        auto state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderLine(renderer, 100, 100, 500, 500);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderPoint(renderer, 300, 50);

        SDL_FRect rect {100.0f, 500.0f, 20.0f, 10.0f};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
