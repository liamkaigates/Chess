#include <game.h>

using namespace std;

int main()
{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    unsigned long time;

    // Initialize SDL
    if (init(&window, &surface, &time) != 0)
    {
        return -1;
    }

    // Run the chess game
    runGame(&window, &surface, &time);

    // Clean up and exit
    close(window);
    return 0;
}