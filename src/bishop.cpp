// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible bishop moves
vector<Move> Game::get_bishop_moves(int i, int j)
{
    vector<Move> bishop_moves;
    int board_index;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';

    // Determine the board index and opposite board based on the current turn
    if (this->whiteTurn)
    {
        board_index = 2; // Assuming index 2 represents white bishops in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 8; // Assuming index 8 represents black bishops in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }

    // Determine the color of the bishop
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate bishop moves based on color

    // Check for valid moves along the diagonal - up right direction
    for (int file = j + 1, rank = i - 1; file < DIMENSION && rank >= 0; ++file, --rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - up left direction
    for (int file = j - 1, rank = i - 1; file >= 0 && rank >= 0; --file, --rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down right direction
    for (int file = j + 1, rank = i + 1; file < DIMENSION && rank < DIMENSION; ++file, ++rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down left direction
    for (int file = j - 1, rank = i + 1; file >= 0 && rank < DIMENSION; --file, ++rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    return bishop_moves;
}