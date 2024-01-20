#include <iostream>
#include <SDL2/SDL.h>
#include "chess.h"

#define SQ_SIZE 60
#define DIMENSION 8
#define MAX_FPS 15
#define set_bit(b, i) ((b) |= (1ULL << i))
#define get_bit(b, i) (((b) & (1ULL << i)) >> i)
#define clear_bit(b, i) ((b) &= ~(1ULL << i))
#define get_LSB(b) (__builtin_ctzll(b))

using namespace std;

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

int loadPieces(SDL_Window **window, SDL_Surface **surface, BitBoard *bitboard)
{
    string piece_path[] = {"wp", "wn", "wb", "wr", "wq", "wk", "bp", "bn", "bb", "br", "bq", "bk"};
    for (int i = 0; i < 12; ++i)
    {
        string path = "Image/" + piece_path[i] + ".bmp";
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

bool search_moves(vector<Move> moves, Move move)
{
    for (int i = 0; i < moves.size(); ++i)
    {
        if (move == moves[i])
        {
            return true;
        }
    }
    return false;
}

Move get_move_object(vector<Move> moves, Move move)
{
    for (int i = 0; i < moves.size(); ++i)
    {
        if (move == moves[i])
        {
            return moves[i];
        }
    }
    return move;
}

void print_move(Move move)
{
    cout << "Piece: " << move.piece
         << " Color: " << move.color
         << " Start: (" << move.start_file << ", " << move.start_rank << ")"
         << " End: (" << move.end_file << ", " << move.end_rank << ")\n";
}

void print_moves(const std::vector<Move> &moves)
{
    cout << moves.size() << " Moves" << endl;
    for (const auto &move : moves)
    {
        print_move(move);
    }
}

int runGame(SDL_Window **window, SDL_Surface **surface, unsigned long *startTime)
{
    Game game = Game();
    vector<Move> valid_moves = game.get_valid_moves();
    print_moves(valid_moves);
    game.board = BitBoard();
    loadPieces(window, surface, &(game.board));
    SDL_Event e;
    bool quit = false;
    bool checkMate = true;
    pair<int, int> square;
    vector<pair<int, int>> clicks;
    unsigned long time = SDL_GetTicks();
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int col = x / SQ_SIZE;
                int row = y / SQ_SIZE;
                if (square == std::make_pair(row, col) || col >= 8 || row >= 8)
                {
                    square = std::make_pair(-1, -1);
                    clicks.clear();
                }
                else
                {
                    square = std::make_pair(row, col);
                    clicks.push_back(square);
                }
                if (clicks.size() == 2)
                {
                    Move move = game.get_move(clicks);
                    printf("User Move\n");
                    print_move(move);
                    if (search_moves(valid_moves, move))
                    {
                        game.make_move(get_move_object(valid_moves, move));
                        valid_moves = game.get_valid_moves();
                        print_moves(valid_moves);
                    }
                    clicks.clear();
                    square = std::make_pair(-1, -1);
                }
            }
            else if (e.type == SDL_KEYDOWN)
            {
                SDL_Keycode keyCode = e.key.keysym.sym;
                if (keyCode == SDLK_z)
                {
                    game.undo_move();
                    valid_moves = game.get_valid_moves();
                    print_moves(valid_moves);
                }
            }
        }
        drawBoard(window, surface);
        drawPieces(window, surface, &(game.board));
        while (time - *startTime < 1000 / MAX_FPS)
        {
            time = SDL_GetTicks();
        }
        *startTime = time;
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
    unsigned long time;
    init(&window, &surface, &time);
    drawBoard(&window, &surface);
    runGame(&window, &surface, &time);
    close(window);
    return 0;
}