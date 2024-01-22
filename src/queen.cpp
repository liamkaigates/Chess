// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible queen moves
vector<Move> Game::get_queen_moves(int i, int j)
{
    vector<Move> queen_moves;
    int board_index;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 4; // Assuming index 4 represents white queens in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 10; // Assuming index 10 represents black queens in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }

    // Determine the color of the queen
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate queen moves based on color

    // Check for valid moves along the rank - right direction
    for (int file = j + 1; file < DIMENSION; ++file)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, i, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the rank - left direction
    for (int file = j - 1; file >= 0; --file)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, i, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - up direction
    for (int rank = i - 1; rank >= 0; --rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, j);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - down direction
    for (int rank = i + 1; rank < DIMENSION; ++rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, j);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - up right direction
    for (int file = j + 1, rank = i - 1; file < DIMENSION && rank >= 0; ++file, --rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - up left direction
    for (int file = j - 1, rank = i - 1; file >= 0 && rank >= 0; --file, --rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down right direction
    for (int file = j + 1, rank = i + 1; file < DIMENSION && rank < DIMENSION; ++file, ++rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down left direction
    for (int file = j - 1, rank = i + 1; file >= 0 && rank < DIMENSION; --file, ++rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    return queen_moves;
}