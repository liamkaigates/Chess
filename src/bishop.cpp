// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible bishop moves
vector<Move> Game::get_bishop_moves(int i, int j)
{
    vector<Move> bishop_moves;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';

    // Determine the board index and opposite board based on the current turn
    if (this->whiteTurn)
    {
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        opposite_board = (this->board).get_white_board();
    }

    // Determine the color of the bishop
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate bishop moves based on color

    // Helper function to check and add diagonal moves
    auto checkAndAddDiagonalMoves = [&](int rankDirection, int fileDirection)
    {
        for (int file = j + fileDirection, rank = i + rankDirection;
             file >= 0 && file < DIMENSION && rank >= 0 && rank < DIMENSION;
             file += fileDirection, rank += rankDirection)
        {
            Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
            if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color))
                break;
        }
    };

    // Check for valid moves along the diagonal - up right direction
    checkAndAddDiagonalMoves(-1, 1);

    // Check for valid moves along the diagonal - up left direction
    checkAndAddDiagonalMoves(-1, -1);

    // Check for valid moves along the diagonal - down right direction
    checkAndAddDiagonalMoves(1, 1);

    // Check for valid moves along the diagonal - down left direction
    checkAndAddDiagonalMoves(1, -1);

    return bishop_moves;
}
