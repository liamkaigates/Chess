#include <map>

using namespace std;

typedef unsigned long long U64;

class BitBoard
{
public:
    U64 boards[12];
    U64 *white_pawns;
    U64 *white_knights;
    U64 *white_bishops;
    U64 *white_rooks;
    U64 *white_queens;
    U64 *white_king;
    U64 *black_pawns;
    U64 *black_knights;
    U64 *black_bishops;
    U64 *black_rooks;
    U64 *black_queens;
    U64 *black_king;
    map<string, SDL_Surface *> image_map;
    BitBoard()
    {
        white_pawns = &boards[0];
        white_knights = &boards[1];
        white_bishops = &boards[2];
        white_rooks = &boards[3];
        white_queens = &boards[4];
        white_king = &boards[5];
        black_pawns = &boards[6];
        black_knights = &boards[7];
        black_bishops = &boards[8];
        black_rooks = &boards[9];
        black_queens = &boards[10];
        black_king = &boards[11];

        *white_pawns = 0xff00;
        *white_knights = 0x42;
        *white_bishops = 0x24;
        *white_rooks = 0x81;
        *white_queens = 0x8;
        *white_king = 0x10;
        *black_pawns = 0xff000000000000;
        *black_knights = 0x4200000000000000;
        *black_bishops = 0x2400000000000000;
        *black_rooks = 0x8100000000000000;
        *black_queens = 0x800000000000000;
        *black_king = 0x1000000000000000;
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
    bool whiteTurn;
    bool white_castle;
    bool black_castle;
    vector<Move> moves;
};