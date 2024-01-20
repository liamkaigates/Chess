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
    map<int, string> piece_map;
    map<string, SDL_Surface *> image_map;
    U64 get_white_board();
    U64 get_black_board();
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
    }
};

class Move
{
public:
    char piece;
    char color;
    int start_file;
    int start_rank;
    int end_file;
    int end_rank;
    bool capture;
    char capture_piece;
    char capture_color;

    // Define the equality operator
    bool operator==(const Move &other) const
    {
        // Compare the attributes of the moves
        return piece == other.piece &&
               color == other.color &&
               start_file == other.start_file &&
               start_rank == other.start_rank &&
               end_file == other.end_file &&
               end_rank == other.end_rank;
    }
};

class Game
{
public:
    BitBoard board;
    bool whiteTurn = true;
    bool white_castle = true;
    bool black_castle = true;
    vector<Move> moves;
    void add_move(Move move);
    void make_move(Move move);
    void print_board(U64 board);
    void print_main_board();
    void clear_boards(int bit);
    void undo_move();
    bool is_empty_square(int i, int bit);
    Move get_move(vector<pair<int, int>> clicks);
    char find_captured_piece(int i, int j);
    Move create_piece_move(char color, char piece, int start_rank, int start_file, int end_rank, int end_file);
    bool add_piece_move(vector<Move> &moves, Move &move, U64 opposite_board, char capture_color, int board_index);
    vector<Move> get_pawn_moves(int i, int j);
    vector<Move> get_rook_moves(int i, int j);
    vector<Move> get_knight_moves(int i, int j);
    vector<Move> get_bishop_moves(int i, int j);
    vector<Move> get_queen_moves(int i, int j);
    vector<Move> get_king_moves(int i, int j);
    vector<Move> get_all_moves();
    vector<Move> get_valid_moves();
};