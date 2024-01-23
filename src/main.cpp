#include <game.h>

using namespace std;

int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    // Initialize SDL
    if (init(&window, &renderer, &time) != 0)
    {
        return -1;
    }

    // Run the chess game
    runGame(&renderer, &time);

    // Clean up and exit
    close(window, renderer);
    return 0;
}