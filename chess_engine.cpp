// Including necessary libraries
#include <iostream>

// Using the standard namespace
using namespace std;

// Defining the data type for bitboard representation
typedef unsigned long long U64;
#define set_bit(b, i) ((b) |= (1ULL << i))
#define get_bit(b, i) ((b) & (1ULL << i))
#define clear_bit(b, i) ((b) &= ~(1ULL << i))
#define get_LSB(b) (__builtin_ctzll(b))

// Initializing bitboard variables for chess pieces
class BitBoard
{
public:
    U64 white_pawns = 0xff00;
    U64 white_knights = 0x42;
    U64 white_bishops = 0x24;
    U64 white_rooks = 0x81;
    U64 white_queens = 0x8;
    U64 white_king = 0x10;
    U64 black_pawns = 0xff000000000000;
    U64 black_knights = 0x4200000000000000;
    U64 black_bishops = 0x2400000000000000;
    U64 black_rooks = 0x8100000000000000;
    U64 black_queens = 0x800000000000000;
    U64 black_king = 0x1000000000000000;
    BitBoard()
    {
        white_pawns = 0xff00;
        white_knights = 0x42;
        white_bishops = 0x24;
        white_rooks = 0x81;
        white_queens = 0x8;
        white_king = 0x10;
        black_pawns = 0xff000000000000;
        black_knights = 0x4200000000000000;
        black_bishops = 0x2400000000000000;
        black_rooks = 0x8100000000000000;
        black_queens = 0x800000000000000;
        black_king = 0x1000000000000000;
    }
    U64 get_global_board()
    {
        return white_pawns | black_pawns | white_knights | black_knights | white_bishops | black_bishops | white_rooks | black_rooks | white_queens | black_queens | white_king | black_king;
    }
};

struct Move
{
    char piece;
    char color;
    char start_file;
    char start_rank;
    char end_file;
    char end_rank;
};

class Game
{
public:
    BitBoard board;
    bool whiteTurn = true;
    bool white_castle = true;
    bool black_castle = true;
    vector<Move> moves;
};

// Main function
int main()
{
    Game game = Game();
    return 0;
}