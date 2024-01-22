// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible rook moves
vector<Move> Game::get_rook_moves(int i, int j)
{
    vector<Move> rook_moves;
    int board_index;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 3; // Assuming index 3 represents white rooks in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 9; // Assuming index 9 represents black rooks in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }

    // Determine the color of the rook
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate rook moves based on color

    // Check for valid moves along the rank - right direction
    for (int file = j + 1; file < DIMENSION; ++file)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, i, file);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the rank - left direction
    for (int file = j - 1; file >= 0; --file)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, i, file);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - up direction
    for (int rank = i - 1; rank >= 0; --rank)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, rank, j);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - down direction
    for (int rank = i + 1; rank < DIMENSION; ++rank)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, rank, j);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    return rook_moves;
}