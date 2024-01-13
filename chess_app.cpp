#include <iostream>
#include <SDL2/SDL.h>

#define SQ_SIZE 80
#define DIMENSION 8
#define MAX_FPS 15
typedef unsigned long long U64;
#define set_bit(b, i) ((b) |= (1ULL << i))
#define get_bit(b, i) ((b) & (1ULL << i))
#define clear_bit(b, i) ((b) &= ~(1ULL << i))
#define get_LSB(b) (__builtin_ctzll(b))

using namespace std;

class BitBoard
{
public:
    U64 boards[12];
    U64 *white_pawns;
    U64 *white_knights;
    U64 *white_bishops;
    U64 *white_rooks;
    U64 *white_queens;
    U64 *white_king;
    U64 *black_pawns;
    U64 *black_knights;
    U64 *black_bishops;
    U64 *black_rooks;
    U64 *black_queens;
    U64 *black_king;

    BitBoard()
    {
        white_pawns = &boards[0];
        white_knights = &boards[1];
        white_bishops = &boards[2];
        white_rooks = &boards[3];
        white_queens = &boards[4];
        white_king = &boards[5];
        black_pawns = &boards[6];
        black_knights = &boards[7];
        black_bishops = &boards[8];
        black_rooks = &boards[9];
        black_queens = &boards[10];
        black_king = &boards[11];

        *white_pawns = 0xff00;
        *white_knights = 0x42;
        *white_bishops = 0x24;
        *white_rooks = 0x81;
        *white_queens = 0x8;
        *white_king = 0x10;
        *black_pawns = 0xff000000000000;
        *black_knights = 0x4200000000000000;
        *black_bishops = 0x2400000000000000;
        *black_rooks = 0x8100000000000000;
        *black_queens = 0x800000000000000;
        *black_king = 0x1000000000000000;
    }
};

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

int loadBoard(SDL_Window **window, SDL_Surface **surface)
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

int loadPieces(SDL_Window **window, SDL_Surface **surface, BitBoard *bitboard)
{
    string piece_path[] = {"wp", "wn", "wb", "wr", "wq", "wk", "bp", "bn", "bb", "br", "bq", "bk"};
    for (int i = 0; i < 12; ++i)
    {
        U64 board = bitboard->boards[i];
        for (int j = 0; j < DIMENSION; ++j)
        {
            for (int k = 0; k < DIMENSION; ++k)
            {
                if (get_bit(board, (j * DIMENSION + k)) >> (j * DIMENSION + k) == 1)
                {
                    SDL_Rect rect = {k * SQ_SIZE, j * SQ_SIZE, SQ_SIZE, SQ_SIZE};
                    string path = "Image/" + piece_path[i] + ".bmp";
                    cout << path << endl;
                    SDL_Surface *piece = SDL_LoadBMP(path.c_str());
                    if (piece == NULL)
                    {
                        printf("Unable to load image %s! SDL Error: %s\n", &path, SDL_GetError());
                        return -1;
                    }
                    SDL_BlitSurface(piece, NULL, *surface, &rect);
                    SDL_UpdateWindowSurface(*window);
                }
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
    SDL_Rect **board = nullptr;
    BitBoard *bitBoard = new BitBoard();
    init(&window, &surface);
    loadBoard(&window, &surface);
    loadPieces(&window, &surface, bitBoard);
    runGame();
    close(window);
    return 0;
}