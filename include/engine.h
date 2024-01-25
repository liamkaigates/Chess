#ifndef ENGINE_H
#define ENGINE_H
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitboard.h>
#include <move.h>

using namespace std;

// Constants
#define SQ_SIZE 60
#define DIMENSION 8
#define MAX_FPS 15

// Bit manipulation macros
#define set_bit(b, i) ((b) |= (1ULL << i))
#define get_bit(b, i) (((b) & (1ULL << i)) >> i)
#define clear_bit(b, i) ((b) &= ~(1ULL << i))
#define get_LSB(b) (__builtin_ctzll(b))

class Game
{
public:
    // Game state variables
    BitBoard board;                              // Bitboard representation of the chess board
    bool whiteTurn = true;                       // Indicates if it's currently white's turn
    bool checkmate = false;                      // Indicates if a checkmate has occurred
    bool stalemate = false;                      // Indicates if a stalemate has occurred
    pair<int, int> white_king_location = {0, 4}; // Location of the white king
    pair<int, int> black_king_location = {7, 4}; // Location of the black king
    bool white_castle = true;                    // Indicates if white can castle
    bool black_castle = true;                    // Indicates if black can castle
    vector<Move> moves;                          // List of moves made in the game
    vector<pair<int, int>> en_passant_pawns;     // List of pawns that can be captured en passant
    // Member functions
    void add_move(Move move);                                                                                   // Adds a move to the list of moves
    void make_move(Move move, bool user);                                                                       // Makes a move on the chess board
    void print_board(U64 board);                                                                                // Prints the given bitboard representation of the chess board
    void print_main_board();                                                                                    // Prints the main chess board
    void clear_boards(int bit);                                                                                 // Clears the bitboards
    void undo_move(bool user);                                                                                  // Undoes the last move made
    bool is_empty_square(int bit);                                                                              // Checks if a square on the chess board is empty
    Move get_move(vector<pair<int, int>> clicks);                                                               // Gets a move from user input
    void print_move(Move move);                                                                                 // Prints a move
    void print_moves(vector<Move> &moves);                                                                      // Prints a list of moves
    char find_captured_piece(int i, int j);                                                                     // Finds the captured piece in a move
    Move create_piece_move(char color, char piece, int start_rank, int start_file, int end_rank, int end_file); // Creates a move for a specific piece
    bool add_piece_move(vector<Move> &moves, Move &move, U64 opposite_board, char capture_color);               // Adds a move for a specific piece
    vector<Move> get_pawn_moves(int i, int j);                                                                  // Gets all possible moves for a pawn
    vector<Move> get_rook_moves(int i, int j);                                                                  // Gets all possible moves for a rook
    vector<Move> get_knight_moves(int i, int j);                                                                // Gets all possible moves for a knight
    vector<Move> get_bishop_moves(int i, int j);                                                                // Gets all possible moves for a bishop
    vector<Move> get_queen_moves(int i, int j);                                                                 // Gets all possible moves for a queen
    vector<Move> get_king_moves(int i, int j);                                                                  // Gets all possible moves for a king
    bool in_check();                                                                                            // Checks if the current player is in check
    bool square_under_attack(int i, int j);                                                                     // Checks if a square on the chess board is under attack
    vector<Move> get_all_moves();                                                                               // Gets all possible moves for the current player
    vector<Move> get_valid_moves();
    void promote_pawn(int square, string piece_type); // Gets all valid moves for the current player
};

#endif // ENGINE_H
