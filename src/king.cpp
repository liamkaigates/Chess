// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible king moves
vector<Move> Game::get_king_moves(int i, int j)
{
    vector<Move> king_moves;
    int board_index;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';

    // Determine the board index and opposite board based on the current turn
    if (this->whiteTurn)
    {
        board_index = 5; // Assuming index 5 represents white kings in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 11; // Assuming index 11 represents black kings in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }

    // Determine the color of the king
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate king moves based on color

    // Define relative positions for king moves
    vector<pair<int, int>> king_squares = {
        {i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}, {i + 1, j + 1}, {i + 1, j - 1}, {i - 1, j - 1}, {i - 1, j + 1}};

    // Check for valid moves within the board boundaries
    for (auto square : king_squares)
    {
        if (square.first >= 0 && square.first < DIMENSION && square.second >= 0 && square.second < DIMENSION)
        {
            Move king_move = this->create_piece_move(color, 'k', i, j, square.first, square.second);
            this->add_piece_move(king_moves, king_move, opposite_board, capture_color, board_index);
        }
    }

    return king_moves;
}
