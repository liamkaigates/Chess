#include "sdl_helper.h"

// Initialize SDL
int init(SDL_Window **window, SDL_Surface **surface, unsigned long *time)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    *time = SDL_GetTicks();

    *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SQ_SIZE * DIMENSION, SQ_SIZE * DIMENSION, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        cout << "Error initializing SDL Window: " << SDL_GetError() << endl;
        return 1;
    }

    *surface = SDL_GetWindowSurface(*window);
    return 0;
}

// Draw the chessboard
int drawBoard(SDL_Window **window, SDL_Surface **surface)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            SDL_Rect rect = {i * SQ_SIZE, j * SQ_SIZE, SQ_SIZE, SQ_SIZE};
            if ((i + j) % 2 == 0)
            {
                SDL_FillRect(*surface, &rect, SDL_MapRGB((*surface)->format, 238, 238, 210));
            }
            else
            {
                SDL_FillRect(*surface, &rect, SDL_MapRGB((*surface)->format, 118, 150, 86));
            }
        }
    }

    SDL_UpdateWindowSurface(*window);
    return 0;
}

// Load chess piece images
int loadPieces(BitBoard *bitboard)
{
    string piece_path[] = {"wp", "wn", "wb", "wr", "wq", "wk", "bp", "bn", "bb", "br", "bq", "bk"};
    for (int i = 0; i < 12; ++i)
    {
        string path = "piece_images/" + piece_path[i] + ".bmp";
        SDL_Surface *piece = SDL_LoadBMP(path.c_str());
        if (piece == NULL)
        {
            printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return -1;
        }
        bitboard->image_map[piece_path[i]] = piece;
    }
    return 0;
}

// Draw chess pieces on the board
int drawPieces(SDL_Window **window, SDL_Surface **surface, BitBoard *bitboard)
{
    string piece_path[] = {"wp", "wn", "wb", "wr", "wq", "wk", "bp", "bn", "bb", "br", "bq", "bk"};
    for (int i = 0; i < 12; ++i)
    {
        U64 board = bitboard->boards[i];
        for (int j = 0; j < DIMENSION; ++j)
        {
            for (int k = 0; k < DIMENSION; ++k)
            {
                if (get_bit(board, (j * DIMENSION + k)) == 1)
                {
                    SDL_Rect rect = {k * SQ_SIZE, (DIMENSION - 1 - j) * SQ_SIZE, SQ_SIZE, SQ_SIZE};
                    SDL_BlitSurface(bitboard->image_map[piece_path[i]], NULL, *surface, &rect);
                }
            }
        }
    }

    SDL_UpdateWindowSurface(*window);
    return 0;
}

// Close the SDL window and clean up
int close(SDL_Window *window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}