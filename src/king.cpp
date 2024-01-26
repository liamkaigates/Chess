// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible king moves
vector<Move> Game::get_king_moves(int i, int j)
{
    vector<Move> king_moves;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    // cout << "Getting king moves" << endl;
    // cout << "i: " << i << " j: " << j << endl;
    // Determine the board index and opposite board based on the current turn
    if (this->whiteTurn)
    {
        opposite_board = (this->board).get_black_board();
    }
    else
    {
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
            this->add_piece_move(king_moves, king_move, opposite_board, capture_color);
        }
    }
    return king_moves;
}

// Function get to castle moves
vector<Move> Game::get_castle_moves(int i, int j)
{
    vector<Move> castle_moves;
    // cout << "Getting king moves" << endl;
    // cout << "i: " << i << " j: " << j << endl;
    // Determine the board index and opposite board based on the current turn

    // Determine the color of the king
    char color = (this->whiteTurn) ? 'w' : 'b';

    if (this->in_check())
    {
        return castle_moves;
    }
    if (((whiteTurn && get_bit(this->castle_right, 0) == 1) || (!whiteTurn && get_bit(this->castle_right, 2) == 1)) && is_empty_square(i * DIMENSION + j + 1) && is_empty_square(i * DIMENSION + j + 2) && square_under_attack(i * DIMENSION + j + 1) == false && square_under_attack(i * DIMENSION + j + 2) == false)
    {
        // cout << "Castle Move King Side" << endl;
        Move king_move = this->create_piece_move(color, 'k', i, j, i, j + 2);
        king_move.is_castle = true;
        king_move.capture = false;
        king_move.is_enpassant = false;
        castle_moves.push_back(king_move);
    }
    if (((whiteTurn && get_bit(this->castle_right, 1) == 1) || (!whiteTurn && get_bit(this->castle_right, 3) == 1)) && is_empty_square(i * DIMENSION + j - 1) && is_empty_square(i * DIMENSION + j - 2) && is_empty_square(i * DIMENSION + j - 3) && square_under_attack(i * DIMENSION + j - 1) == false && square_under_attack(i * DIMENSION + j - 2) == false)
    {
        // cout << "Castle Move Queen Side" << endl;
        Move king_move = this->create_piece_move(color, 'k', i, j, i, j - 2);
        king_move.is_castle = true;
        king_move.capture = false;
        king_move.is_enpassant = false;
        castle_moves.push_back(king_move);
    }

    // cout << "Castle moves: " << castle_moves.size() << endl;
    return castle_moves;
}