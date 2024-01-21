#pragma once
#include <SDL2/SDL.h>
#include <engine.h>

// Function prototypes
int init(SDL_Window **window, SDL_Surface **surface, unsigned long *time);
int drawBoard(SDL_Window **window, SDL_Surface **surface);
int loadPieces(BitBoard *bitboard);
int drawPieces(SDL_Window **window, SDL_Surface **surface, BitBoard *bitboard);
int close(SDL_Window *window);