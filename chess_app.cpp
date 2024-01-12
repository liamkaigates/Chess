#include <iostream>
#include <SDL2/SDL.h>

#define SQ_SIZE 80
#define DIMENSION 8
#define MAX_FPS 15
#define IMAGES map<string, SDL_Texture *>

using namespace std;

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    else
    {
        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SQ_SIZE * 8, SQ_SIZE * 8, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            surface = SDL_GetWindowSurface(window);
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}