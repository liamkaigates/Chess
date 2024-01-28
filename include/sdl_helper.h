#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <engine.h>

// Function prototypes
int init(SDL_Window **window, SDL_Renderer **renderer);
int drawBoard(SDL_Renderer **renderer);
int loadPieces(BitBoard *bitboard, SDL_Renderer **renderer);
int drawPieces(SDL_Renderer **renderer, BitBoard *bitboard);
void draw_circle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void highlight_valid_squares(SDL_Renderer *renderer, vector<Move> validMoves, pair<int, int> square);
int animate(SDL_Renderer **renderer, Game game, Move move);
void endgame(SDL_Renderer **renderer, Game &game, bool checkmate);
int close(SDL_Window *window, SDL_Renderer *renderer);