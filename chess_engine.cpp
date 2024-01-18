// Including necessary libraries
#include <iostream>
#include <SDL2/SDL.h>
#include "chess.h"
#include <vector>
#include <algorithm>

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

Move Game::get_move(vector<pair<int, int>> clicks)
{
    int square = (DIMENSION - 1 - clicks[0].first) * DIMENSION + clicks[0].second;
    Move move;
    move.start_file = (DIMENSION - 1 - clicks[0].first);
    move.start_rank = clicks[0].second;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, square) == 1)
        {
            move.color = (*this).board.piece_map[i][0];
            move.piece = (*this).board.piece_map[i][1];
            move.end_file = (DIMENSION - 1 - clicks[1].first);
            move.end_rank = clicks[1].second;
            return move;
        }
    }
    return move;
}

void Game::make_move(Move move)
{
    cout << "Make Move" << endl;
    int startSquare = move.start_file * DIMENSION + move.start_rank;
    int endSquare = move.end_file * DIMENSION + move.end_rank;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, startSquare) == 1)
        {
            clear_bit(board, startSquare);
            clear_boards(endSquare);
            set_bit(board, endSquare);
            this->add_move(move);
            this->whiteTurn = !this->whiteTurn;
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
                this->whiteTurn = !this->whiteTurn;
                break;
            }
        }
        print_main_board();
    }
}

bool Game::is_empty_square(int i, int bit)
{
    U64 result = 0;
    for (int j = 0; j < 12; ++j)
    {
        if (j != i)
        {
            result |= (this->board).boards[j];
        }
    }
    return (get_bit(result, bit) == 0);
}

vector<Move> Game::get_pawn_moves(int i, int j)
{
    vector<Move> pawn_moves;
    int board_index;
    U64 pawn_board;
    if (this->whiteTurn)
    {
        board_index = 0;
    }
    else
    {
        board_index = 1;
    }
    pawn_board = (this->board).boards[board_index];

    // Determine the color of the pawn
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate pawn moves based on color
    int forward_direction = (this->whiteTurn) ? 1 : -1;

    // Check for valid moves (e.g., check if the move is within the board boundaries)
    if (this->is_empty_square(board_index, j + DIMENSION * (forward_direction + i)))
    {
        // Add the pawn move to the vector
        Move pawn_move;
        pawn_move.piece = 'p';
        pawn_move.color = color;
        pawn_move.start_file = i;
        pawn_move.start_rank = j;
        pawn_move.end_file = i + forward_direction;
        pawn_move.end_rank = j;

        pawn_moves.push_back(pawn_move);
    }

    if (this->is_empty_square(board_index, j + DIMENSION * (forward_direction * 2 + i)))
    {
        // Add the pawn move to the vector
        Move pawn_move;
        pawn_move.piece = 'p';
        pawn_move.color = color;
        pawn_move.start_file = j;
        pawn_move.start_file = i;
        pawn_move.start_rank = j;
        pawn_move.end_file = i + forward_direction * 2;
        pawn_move.end_rank = j;

        pawn_moves.push_back(pawn_move);
    }

    // Add additional logic for capturing moves, en passant, etc.
    // ...
    return pawn_moves;
}

vector<Move> Game::get_all_moves()
{
    vector<Move> all_moves;

    for (int i = 0; i < 12; ++i)
    {
        U64 board = (this->board).boards[i];

        for (int j = 0; j < DIMENSION; ++j)
        {
            for (int k = 0; k < DIMENSION; ++k)
            {
                if (get_bit(board, (j * DIMENSION + k)) == 1)
                {
                    string piece = (this->board).piece_map[i];

                    // Updated switch statement to use strcmp for string comparison
                    if (piece == "wp" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wp"
                        vector<Move> pawn_moves = this->get_pawn_moves(j, k);
                        all_moves.insert(all_moves.end(), pawn_moves.begin(), pawn_moves.end());
                    }
                    else if (piece == "wr" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wr"
                        /* code */
                    }
                    else if (piece == "wn" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wn"
                        /* code */
                    }
                    else if (piece == "wb" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wb"
                        /* code */
                    }
                    else if (piece == "wq" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wq"
                        /* code */
                    }
                    else if (piece == "wk" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wk"
                        /* code */
                    }
                    else if (piece == "bp" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bp"
                        /* code */
                        vector<Move> pawn_moves = this->get_pawn_moves(j, k);
                        all_moves.insert(all_moves.end(), pawn_moves.begin(), pawn_moves.end());
                    }
                    else if (piece == "br" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "br"
                        /* code */
                    }
                    else if (piece == "bn" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bn"
                        /* code */
                    }
                    else if (piece == "bb" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bb"
                        /* code */
                    }
                    else if (piece == "bq" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bq"
                        /* code */
                    }
                    else if (piece == "bk" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bk"
                        /* code */
                    }
                }
            }
        }
    }
    cout << all_moves.size() << " Moves" << endl;
    return all_moves;
}

vector<Move> Game::get_valid_moves()
{
    vector<Move> all_moves = get_all_moves();
    vector<Move> valid_moves = all_moves;
    return valid_moves;
}