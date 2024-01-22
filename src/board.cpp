// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Print a move object
void Game::print_move(Move move)
{
    cout << "Piece: " << move.piece
         << " Color: " << move.color
         << " Start: (" << move.start_file << ", " << move.start_rank << ")"
         << " End: (" << move.end_file << ", " << move.end_rank << ")\n";
}

// Print a vector of moves
void Game ::print_moves(vector<Move> &moves)
{
    cout << moves.size() << " Moves" << endl;
    for (const auto &move : moves)
    {
        print_move(move);
    }
}

// Function to get the white board
U64 BitBoard::get_white_board()
{
    return boards[0] | boards[1] | boards[2] | boards[3] | boards[4] | boards[5];
}

// Function to get the black board
U64 BitBoard::get_black_board()
{
    return boards[6] | boards[7] | boards[8] | boards[9] | boards[10] | boards[11];
}