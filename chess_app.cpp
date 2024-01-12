#include <iostream>
#include <SDL2/SDL.h>

#define SQ_SIZE 80
#define DIMENSION 8
#define MAX_FPS 15
#define IMAGES map<string, SDL_Texture *>

using namespace std;

int init(SDL_Window **window, SDL_Surface **surface)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }
    *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SQ_SIZE * DIMENSION, SQ_SIZE * DIMENSION, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        cout << "Error initializing SDL Window: " << SDL_GetError() << endl;
        return 1;
    }
    *surface = SDL_GetWindowSurface(*window);
    return 0;
}

int loadBoard(SDL_Window **window, SDL_Surface **surface, SDL_Surface ***board)
{
    SDL_FillRect(*surface, nullptr, SDL_MapRGB((*surface)->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(*window);
    char notation[3] = "A1";
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            notation[0] = 'H' - i;
            notation[1] = '1' + j;
            cout << notation << endl;
            if ((i + j) % 2 == 0)
            {
            }
            else
            {
            }
        }
    }
    return 0;
}

int loadPieces(SDL_Window **window, SDL_Surface **surface, SDL_Surface ***board)
{
    SDL_FillRect(*surface, nullptr, SDL_MapRGB((*surface)->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(*window);
    char notation[3] = "A1";
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            notation[0] = 'H' - i;
            notation[1] = '1' + j;
            cout << notation << endl;
            if ((i + j) % 2 == 0)
            {
            }
            else
            {
            }
        }
    }
    return 0;
}

int runGame()
{
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
    return 0;
}

int close(SDL_Window *window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Surface **board = nullptr;

    init(&window, &surface);
    loadBoard(&window, &surface, &board);
    loadPieces(&window, &surface, &board);
    runGame();
    close(window);
    return 0;
}