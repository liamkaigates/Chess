// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible moves for a pawn
vector<Move> Game::get_pawn_moves(int i, int j)
{
    vector<Move> pawn_moves;

    char color = (this->whiteTurn) ? 'w' : 'b';
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    int forward_direction = (this->whiteTurn) ? 1 : -1;
    U64 capture_board = (this->whiteTurn) ? (this->board).get_black_board() : (this->board).get_white_board();
    int two_move_rank = (this->whiteTurn) ? 1 : 6;

    // Check if the square in front of the pawn is empty
    if (this->is_empty_square(j + DIMENSION * (forward_direction + i)))
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + forward_direction, j);
        pawn_move.promotion = (i + forward_direction == 7) || (i + forward_direction == 0);
        pawn_move.capture = false;
        pawn_moves.push_back(pawn_move);
    }

    // Check if the pawn can move two squares forward from its starting position
    if (two_move_rank == i && this->is_empty_square(j + DIMENSION * (forward_direction + i)) && this->is_empty_square(j + DIMENSION * (forward_direction * 2 + i)))
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + forward_direction * 2, j);
        pawn_move.capture = false;
        pawn_moves.push_back(pawn_move);
    }

    // Check if the pawn can capture a piece to the left
    if (j > 0 && get_bit(capture_board, ((j - 1) + DIMENSION * (forward_direction + i))) == 1)
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + forward_direction, j - 1);
        pawn_move.capture = true;
        pawn_move.capture_piece = this->find_captured_piece(i + forward_direction, j - 1);
        pawn_move.capture_color = capture_color;
        pawn_move.promotion = (i + forward_direction == 7) || (i + forward_direction == 0);
        pawn_moves.push_back(pawn_move);
    }

    // Check if the pawn can capture a piece to the right
    if (j < 7 && get_bit(capture_board, ((j + 1) + DIMENSION * (forward_direction + i))) == 1)
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + forward_direction, j + 1);
        pawn_move.capture = true;
        pawn_move.capture_piece = this->find_captured_piece(i + forward_direction, j + 1);
        pawn_move.capture_color = capture_color;
        pawn_move.promotion = (i + forward_direction == 7) || (i + forward_direction == 0);
        pawn_moves.push_back(pawn_move);
    }

    return pawn_moves;
}
