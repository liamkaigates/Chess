// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible knight moves
vector<Move> Game::get_knight_moves(int i, int j)
{
    vector<Move> knight_moves;
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

    // Determine the color of the knight
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate knight moves based on color

    // Define relative positions for knight moves
    vector<pair<int, int>> knight_squares = {
        {i - 2, j + 1}, {i - 1, j + 2}, {i + 1, j + 2}, {i + 2, j + 1}, {i + 2, j - 1}, {i + 1, j - 2}, {i - 1, j - 2}, {i - 2, j - 1}};

    // Check for valid moves within the board boundaries
    for (auto square : knight_squares)
    {
        if (square.first >= 0 && square.first < DIMENSION && square.second >= 0 && square.second < DIMENSION)
        {
            Move knight_move = this->create_piece_move(color, 'n', i, j, square.first, square.second);
            this->add_piece_move(knight_moves, knight_move, opposite_board, capture_color);
        }
    }

    return knight_moves;
}
