// Including necessary libraries
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

// Using the standard namespace
using namespace std;

void Game::add_move(Move move)
{
    (*this).moves.push_back(move);
}

void Game::print_board(U64 board)
{
    for (int row = 0; row < DIMENSION; row++)
    {
        for (int col = 0; col < DIMENSION; col++)
        {
            int index = row * DIMENSION + col;
            if (get_bit(board, index) != 0)
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void Game::print_main_board()
{
    printf("Main Board\n");
    U64 result = 0;
    for (int i = 0; i < 12; ++i)
    {
        result |= (this->board).boards[i];
    }
    print_board(result);
}

void Game::clear_boards(int bit)
{
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        clear_bit(board, bit);
    }
}

void Game::make_move(vector<pair<int, int>> clicks)
{
    int startSquare = (DIMENSION - 1 - clicks[0].first) * DIMENSION + clicks[0].second;
    int endSquare = (DIMENSION - 1 - clicks[1].first) * DIMENSION + clicks[1].second;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, startSquare) == 1)
        {
            clear_bit(board, startSquare);
            clear_boards(endSquare);
            set_bit(board, endSquare);
            print_main_board();
            Move move = {
                (*this).board.piece_map[i][1],
                (*this).board.piece_map[i][0],
                (DIMENSION - 1 - clicks[0].first),
                clicks[0].second,
                (DIMENSION - 1 - clicks[1].first),
                clicks[1].second};
            this->add_move(move);
            break;
        }
    }
}

void Game::undo_move()
{
    printf("Undo Move\n");
    if (!moves.empty())
    {
        Move move = moves.back();
        moves.pop_back();
        cout << move.color << move.piece << endl;
        int startSquare = move.start_file * DIMENSION + move.start_rank;
        int endSquare = move.end_file * DIMENSION + move.end_rank;

        for (int i = 0; i < 12; ++i)
        {
            U64 &board = (*this).board.boards[i];
            if (get_bit(board, endSquare) == 1)
            {
                clear_bit(board, endSquare);
                clear_boards(startSquare);
                set_bit(board, startSquare);
                break;
            }
        }
        print_main_board();
    }
}