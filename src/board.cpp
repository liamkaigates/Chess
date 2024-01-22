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

void Game::print_board(U64 board)
{
    // Print the top border
    cout << "  +---+---+---+---+---+---+---+---+\n";

    // Iterate through each square on the board
    for (int i = 0; i < DIMENSION; ++i)
    {
        // Print the left border
        cout << DIMENSION - i << " | ";

        // Iterate through each square on the board
        for (int j = 0; j < DIMENSION; ++j)
        {
            // Print the piece occupying the square
            cout << ((get_bit(board, (i * DIMENSION + j)) == 1) ? "X" : " ") << " | ";
        }

        // Print the right border
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }

    // Print the bottom border
    cout << "    A   B   C   D   E   F   G   H\n";
}

void Game::print_main_board()
{

    print_board((this->board).get_white_board() | (this->board).get_black_board());
}

// Print a vector of moves
void Game::print_moves(vector<Move> &moves)
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
    // Combine the white piece boards using bitwise OR
    return boards[0] | boards[1] | boards[2] | boards[3] | boards[4] | boards[5];
}

// Function to get the black board
U64 BitBoard::get_black_board()
{
    // Combine the black piece boards using bitwise OR
    return boards[6] | boards[7] | boards[8] | boards[9] | boards[10] | boards[11];
}

// Function to clear a specific bit on all piece boards
void Game::clear_boards(int bit)
{
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        clear_bit(board, bit);
    }
}
