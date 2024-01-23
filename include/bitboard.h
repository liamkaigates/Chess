#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>

using namespace std;

typedef unsigned long long U64;

class BitBoard
{
public:
    // Bitboards for each piece type
    U64 boards[12];

    // Pointers to individual piece bitboards
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

    // Maps to associate piece names and bitboards
    map<int, string> piece_map;
    map<string, U64 *> board_map;
    map<string, SDL_Texture *> image_map;

    // Function to get the bitboard for all white pieces
    U64 get_white_board();

    // Function to get the bitboard for all black pieces
    U64 get_black_board();

    // Constructor
    BitBoard()
    {
        // Initialize the pointers to individual piece bitboards
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

        // Initialize the bitboards for each piece type
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

        // Initialize the piece name to bitboard mapping
        piece_map[0] = "wp";
        piece_map[1] = "wn";
        piece_map[2] = "wb";
        piece_map[3] = "wr";
        piece_map[4] = "wq";
        piece_map[5] = "wk";
        piece_map[6] = "bp";
        piece_map[7] = "bn";
        piece_map[8] = "bb";
        piece_map[9] = "br";
        piece_map[10] = "bq";
        piece_map[11] = "bk";

        // Initialize the piece name to bitboard pointer mapping
        board_map["wp"] = &boards[0];
        board_map["wn"] = &boards[1];
        board_map["wb"] = &boards[2];
        board_map["wr"] = &boards[3];
        board_map["wq"] = &boards[4];
        board_map["wk"] = &boards[5];
        board_map["bp"] = &boards[6];
        board_map["bn"] = &boards[7];
        board_map["bb"] = &boards[8];
        board_map["br"] = &boards[9];
        board_map["bq"] = &boards[10];
        board_map["bk"] = &boards[11];
    }
};