// Including necessary libraries
#include <iostream>
#include <SDL2/SDL.h>
#include "chess.h"
#include <vector>
#include <algorithm>

#define SQ_SIZE 60
#define DIMENSION 8
#define MAX_FPS 15
#define set_bit(b, i) ((b) |= (1ULL << i))
#define get_bit(b, i) (((b) & (1ULL << i)) >> i)
#define clear_bit(b, i) ((b) &= ~(1ULL << i))
#define get_LSB(b) (__builtin_ctzll(b))

// Using the standard namespace
using namespace std;

U64 BitBoard::get_white_board()
{
    return boards[0] | boards[1] | boards[2] | boards[3] | boards[4] | boards[5];
}

U64 BitBoard::get_black_board()
{
    return boards[6] | boards[7] | boards[8] | boards[9] | boards[10] | boards[11];
}

void Game::add_move(Move move)
{
    (*this).moves.push_back(move);
}

void Game::print_board(U64 board)
{
    for (int row = 0; row < DIMENSION; row++)
    {
        for (int col = 0; col < DIMENSION; col++)
        {
            int index = row * DIMENSION + col;
            if (get_bit(board, index) != 0)
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void Game::print_main_board()
{
    printf("Main Board\n");
    U64 result = 0;
    for (int i = 0; i < 12; ++i)
    {
        result |= (this->board).boards[i];
    }
    print_board(result);
}

void Game::clear_boards(int bit)
{
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        clear_bit(board, bit);
    }
}

char Game::find_captured_piece(int i, int j)
{
    int endSquare = i * DIMENSION + j;

    // Check each piece type on the board to see if it occupies the destination square
    for (int i = 0; i < 12; ++i)
    {
        U64 board = (this->board).boards[i];
        if (get_bit(board, endSquare) == 1)
        {
            return (this->board).piece_map[i][1]; // Return the piece type (e.g., 'p', 'r', 'n', 'b', 'q', 'k')
        }
    }

    return '\0'; // Return null character if no piece is found
}

Move Game::get_move(vector<pair<int, int>> clicks)
{
    int square = (DIMENSION - 1 - clicks[0].first) * DIMENSION + clicks[0].second;
    Move move;
    move.start_rank = (DIMENSION - 1 - clicks[0].first);
    move.start_file = clicks[0].second;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, square) == 1)
        {
            move.color = (*this).board.piece_map[i][0];
            move.piece = (*this).board.piece_map[i][1];
            move.end_rank = (DIMENSION - 1 - clicks[1].first);
            move.end_file = clicks[1].second;
            return move;
        }
    }
    return move;
}

void Game::make_move(Move move)
{
    cout << "Make Move" << endl;
    int startSquare = move.start_rank * DIMENSION + move.start_file;
    int endSquare = move.end_rank * DIMENSION + move.end_file;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, startSquare) == 1)
        {
            clear_bit(board, startSquare);
            clear_boards(endSquare);
            set_bit(board, endSquare);
            this->add_move(move);
            this->whiteTurn = !this->whiteTurn;
            break;
        }
    }
}

void Game::undo_move()
{
    printf("Undo Move\n");
    if (!moves.empty())
    {
        Move move = moves.back();
        moves.pop_back();
        cout << move.capture << endl;
        int startSquare = move.start_rank * DIMENSION + move.start_file;
        int endSquare = move.end_rank * DIMENSION + move.end_file;
        char capturedPiece = move.capture_piece;
        for (int i = 0; i < 12; ++i)
        {
            U64 &board = (*this).board.boards[i];
            if (get_bit(board, endSquare) == 1)
            {
                clear_bit(board, endSquare);
                clear_boards(startSquare);
                set_bit(board, startSquare);
                this->whiteTurn = !this->whiteTurn;
                if (move.capture)
                {
                    // Add back the captured piece to its respective board
                    switch (capturedPiece)
                    {
                    case 'p':
                        if (move.color == 'w')
                            set_bit((this->board).boards[6], endSquare);
                        else
                            set_bit((this->board).boards[0], endSquare);
                        break;
                    case 'r':
                        if (move.color == 'w')
                            set_bit((this->board).boards[9], endSquare);
                        else
                            set_bit((this->board).boards[3], endSquare);
                        break;
                    case 'n':
                        if (move.color == 'w')
                            set_bit((this->board).boards[7], endSquare);
                        else
                            set_bit((this->board).boards[1], endSquare);
                        break;
                    case 'b':
                        if (move.color == 'w')
                            set_bit((this->board).boards[8], endSquare);
                        else
                            set_bit((this->board).boards[4], endSquare);
                        break;
                    case 'q':
                        if (move.color == 'w')
                            set_bit((this->board).boards[10], endSquare);
                        else
                            set_bit((this->board).boards[5], endSquare);
                        break;
                    case 'k':
                        if (move.color == 'w')
                            set_bit((this->board).boards[11], endSquare);
                        else
                            set_bit((this->board).boards[5], endSquare);
                        break;
                    default:
                        break;
                    }
                }
                break;
            }
        }
    }
}

bool Game::is_empty_square(int i, int bit)
{
    U64 result = 0;
    for (int j = 0; j < 12; ++j)
    {
        if (j != i)
        {
            result |= (this->board).boards[j];
        }
    }
    return (get_bit(result, bit) == 0);
}

vector<Move> Game::get_pawn_moves(int i, int j)
{
    vector<Move> pawn_moves;
    int board_index = (this->whiteTurn) ? 0 : 6;
    U64 pawn_board = (this->board).boards[board_index];
    char color = (this->whiteTurn) ? 'w' : 'b';
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    int forward_direction = (this->whiteTurn) ? 1 : -1;
    int two_move_rank = (this->whiteTurn) ? 1 : 6;

    if (this->is_empty_square(board_index, j + DIMENSION * (forward_direction + i)))
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + forward_direction, j);
        pawn_moves.push_back(pawn_move);
    }

    if (two_move_rank == i && this->is_empty_square(board_index, j + DIMENSION * (forward_direction + i)) && this->is_empty_square(board_index, j + DIMENSION * (forward_direction * 2 + i)))
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + forward_direction * 2, j);
        pawn_moves.push_back(pawn_move);
    }

    if (this->whiteTurn && i < 7 && j > 0 && get_bit((this->board).get_black_board(), (j - 1 + DIMENSION * (1 + i))) == 1)
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + 1, j - 1);
        pawn_move.capture = true;
        pawn_move.capture_piece = this->find_captured_piece(i + 1, j - 1);
        pawn_move.capture_color = capture_color;
        pawn_moves.push_back(pawn_move);
    }

    if (this->whiteTurn && i < 7 && j < 7 && get_bit((this->board).get_black_board(), (j + 1 + DIMENSION * (1 + i))) == 1)
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i + 1, j + 1);
        pawn_move.capture = true;
        pawn_move.capture_piece = this->find_captured_piece(i + 1, j + 1);
        pawn_move.capture_color = capture_color;
        pawn_moves.push_back(pawn_move);
    }

    if (!(this->whiteTurn) && i > 0 && j > 0 && get_bit((this->board).get_white_board(), (j - 1 + DIMENSION * (i - 1))) == 1)
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i - 1, j - 1);
        pawn_move.capture = true;
        pawn_move.capture_piece = this->find_captured_piece(i - 1, j - 1);
        pawn_move.capture_color = capture_color;
        pawn_moves.push_back(pawn_move);
    }

    if (!(this->whiteTurn) && i > 0 && j < 7 && get_bit((this->board).get_white_board(), (j + 1 + DIMENSION * (i - 1))) == 1)
    {
        Move pawn_move = this->create_piece_move(color, 'p', i, j, i - 1, j + 1);
        pawn_move.capture = true;
        pawn_move.capture_piece = this->find_captured_piece(i - 1, j + 1);
        pawn_move.capture_color = capture_color;
        pawn_moves.push_back(pawn_move);
    }

    return pawn_moves;
}

// Function to create a rook move
Move Game::create_piece_move(char color, char piece, int start_rank, int start_file, int end_rank, int end_file)
{
    Move move;
    move.piece = piece;
    move.color = color;
    move.start_file = start_file;
    move.start_rank = start_rank;
    move.end_file = end_file;
    move.end_rank = end_rank;
    return move;
}

// Function to add a rook move to the list of moves
bool Game::add_piece_move(vector<Move> &moves, Move &move, U64 opposite_board, char capture_color, int board_index)
{
    if (this->is_empty_square(board_index, (move.end_file + DIMENSION * move.end_rank)))
    {
        moves.push_back(move);
    }
    else
    {
        if (get_bit(opposite_board, (move.end_file + DIMENSION * move.end_rank)) == 1)
        {
            move.capture = true;
            move.capture_piece = this->find_captured_piece(move.end_rank, move.end_file);
            move.capture_color = capture_color;
            moves.push_back(move);
        }
        return true;
    }
    return false;
}

// Function to get all possible rook moves
vector<Move> Game::get_rook_moves(int i, int j)
{
    vector<Move> rook_moves;
    int board_index;
    U64 rook_board;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 3; // Assuming index 3 represents white rooks in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 9; // Assuming index 9 represents black rooks in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }
    rook_board = (this->board).boards[board_index];

    // Determine the color of the rook
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate rook moves based on color

    // Check for valid moves along the rank - right direction
    for (int file = j + 1; file < DIMENSION; ++file)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, i, file);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the rank - left direction
    for (int file = j - 1; file >= 0; --file)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, i, file);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - up direction
    for (int rank = i - 1; rank >= 0; --rank)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, rank, j);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - down direction
    for (int rank = i + 1; rank < DIMENSION; ++rank)
    {
        Move rook_move = this->create_piece_move(color, 'r', i, j, rank, j);
        if (this->add_piece_move(rook_moves, rook_move, opposite_board, capture_color, board_index))
            break;
    }

    return rook_moves;
}

// Function to get all possible bishop moves
vector<Move> Game::get_bishop_moves(int i, int j)
{
    vector<Move> bishop_moves;
    int board_index;
    U64 bishop_board;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 2; // Assuming index 4 represents white bishops in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 8; // Assuming index 10 represents black bishops in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }
    bishop_board = (this->board).boards[board_index];

    // Determine the color of the bishop
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate bishop moves based on color

    // Check for valid moves along the diagonal - up right direction
    for (int file = j + 1, rank = i - 1; file < DIMENSION && rank >= 0; ++file, --rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - up left direction
    for (int file = j - 1, rank = i - 1; file >= 0 && rank >= 0; --file, --rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down right direction
    for (int file = j + 1, rank = i + 1; file < DIMENSION && rank < DIMENSION; ++file, ++rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down left direction
    for (int file = j - 1, rank = i + 1; file >= 0 && rank < DIMENSION; --file, ++rank)
    {
        Move bishop_move = this->create_piece_move(color, 'b', i, j, rank, file);
        if (this->add_piece_move(bishop_moves, bishop_move, opposite_board, capture_color, board_index))
            break;
    }

    return bishop_moves;
}

// Function to get all possible knight moves
vector<Move> Game::get_knight_moves(int i, int j)
{
    vector<Move> knight_moves;
    int board_index;
    U64 knight_board;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 1; // Assuming index 1 represents white knights in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 7; // Assuming index 7 represents black knights in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }
    knight_board = (this->board).boards[board_index];

    // Determine the color of the knight
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate knight moves based on color

    // Check for valid moves along the rank - right direction
    vector<pair<int, int>> knight_squares = {{i - 2, j + 1}, {i - 1, j + 2}, {i + 1, j + 2}, {i + 2, j + 1}, {i + 2, j - 1}, {i + 1, j - 2}, {i - 1, j - 2}, {i - 2, j - 1}};

    for (auto square : knight_squares)
    {
        if (square.first >= 0 && square.first < DIMENSION && square.second >= 0 && square.second < DIMENSION)
        {
            Move knight_move = this->create_piece_move(color, 'n', i, j, square.first, square.second);
            this->add_piece_move(knight_moves, knight_move, opposite_board, capture_color, board_index);
        }
    }

    return knight_moves;
}

// Function to get all possible queen moves
vector<Move> Game::get_queen_moves(int i, int j)
{
    vector<Move> queen_moves;
    int board_index;
    U64 queen_board;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 4; // Assuming index 4 represents white queens in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 10; // Assuming index 10 represents black queens in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }
    queen_board = (this->board).boards[board_index];

    // Determine the color of the queen
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate queen moves based on color

    // Check for valid moves along the rank - right direction
    for (int file = j + 1; file < DIMENSION; ++file)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, i, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the rank - left direction
    for (int file = j - 1; file >= 0; --file)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, i, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - up direction
    for (int rank = i - 1; rank >= 0; --rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, j);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the file - down direction
    for (int rank = i + 1; rank < DIMENSION; ++rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, j);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - up right direction
    for (int file = j + 1, rank = i - 1; file < DIMENSION && rank >= 0; ++file, --rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - up left direction
    for (int file = j - 1, rank = i - 1; file >= 0 && rank >= 0; --file, --rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down right direction
    for (int file = j + 1, rank = i + 1; file < DIMENSION && rank < DIMENSION; ++file, ++rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    // Check for valid moves along the diagonal - down left direction
    for (int file = j - 1, rank = i + 1; file >= 0 && rank < DIMENSION; --file, ++rank)
    {
        Move queen_move = this->create_piece_move(color, 'q', i, j, rank, file);
        if (this->add_piece_move(queen_moves, queen_move, opposite_board, capture_color, board_index))
            break;
    }

    return queen_moves;
}

// Function to get all possible king moves
vector<Move> Game::get_king_moves(int i, int j)
{
    vector<Move> king_moves;
    int board_index;
    U64 king_board;
    U64 opposite_board;
    char capture_color = (this->whiteTurn) ? 'b' : 'w';
    if (this->whiteTurn)
    {
        board_index = 5; // Assuming index 1 represents white kings in the BitBoard class
        opposite_board = (this->board).get_black_board();
    }
    else
    {
        board_index = 11; // Assuming index 7 represents black kings in the BitBoard class
        opposite_board = (this->board).get_white_board();
    }
    king_board = (this->board).boards[board_index];

    // Determine the color of the king
    char color = (this->whiteTurn) ? 'w' : 'b';

    // Generate king moves based on color

    // Check for valid moves along the rank - right direction
    vector<pair<int, int>> king_squares = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}, {i + 1, j + 1}, {i + 1, j - 1}, {i - 1, j - 1}, {i - 1, j + 1}};

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

// Function to get all possible moves for all pieces on the board
vector<Move> Game::get_all_moves()
{
    vector<Move> all_moves;

    for (int i = 0; i < 12; ++i)
    {
        U64 board = (this->board).boards[i];

        for (int j = 0; j < DIMENSION; ++j)
        {
            for (int k = 0; k < DIMENSION; ++k)
            {
                if (get_bit(board, (j * DIMENSION + k)) == 1)
                {
                    string piece = (this->board).piece_map[i];

                    // Updated switch statement to use strcmp for string comparison
                    if (piece == "wp" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wp"
                        vector<Move> pawn_moves = this->get_pawn_moves(j, k);
                        all_moves.insert(all_moves.end(), pawn_moves.begin(), pawn_moves.end());
                    }
                    else if (piece == "wr" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wr"
                        vector<Move> rook_moves = this->get_rook_moves(j, k);
                        all_moves.insert(all_moves.end(), rook_moves.begin(), rook_moves.end());
                    }
                    else if (piece == "wn" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wn"
                        vector<Move> knight_moves = this->get_knight_moves(j, k);
                        all_moves.insert(all_moves.end(), knight_moves.begin(), knight_moves.end());
                    }
                    else if (piece == "wb" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wb"
                        vector<Move> bishop_moves = this->get_bishop_moves(j, k);
                        all_moves.insert(all_moves.end(), bishop_moves.begin(), bishop_moves.end());
                    }
                    else if (piece == "wq" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wq"
                        vector<Move> queen_moves = this->get_queen_moves(j, k);
                        all_moves.insert(all_moves.end(), queen_moves.begin(), queen_moves.end());
                    }
                    else if (piece == "wk" && this->whiteTurn)
                    {
                        // Handle the case when the piece is "wk"
                        vector<Move> king_moves = this->get_king_moves(j, k);
                        all_moves.insert(all_moves.end(), king_moves.begin(), king_moves.end());
                    }
                    else if (piece == "bp" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bp"
                        // TODO: Implement pawn moves
                        vector<Move> pawn_moves = this->get_pawn_moves(j, k);
                        all_moves.insert(all_moves.end(), pawn_moves.begin(), pawn_moves.end());
                    }
                    else if (piece == "br" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "br"
                        vector<Move> rook_moves = this->get_rook_moves(j, k);
                        all_moves.insert(all_moves.end(), rook_moves.begin(), rook_moves.end());
                    }
                    else if (piece == "bn" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bn"
                        vector<Move> knight_moves = this->get_knight_moves(j, k);
                        all_moves.insert(all_moves.end(), knight_moves.begin(), knight_moves.end());
                    }
                    else if (piece == "bb" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bb"
                        vector<Move> bishop_moves = this->get_bishop_moves(j, k);
                        all_moves.insert(all_moves.end(), bishop_moves.begin(), bishop_moves.end());
                    }
                    else if (piece == "bq" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bq"
                        vector<Move> queen_moves = this->get_queen_moves(j, k);
                        all_moves.insert(all_moves.end(), queen_moves.begin(), queen_moves.end());
                    }
                    else if (piece == "bk" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is "bk"
                        vector<Move> king_moves = this->get_king_moves(j, k);
                        all_moves.insert(all_moves.end(), king_moves.begin(), king_moves.end());
                    }
                }
            }
        }
    }
    return all_moves;
}

// Function to get valid moves
vector<Move> Game::get_valid_moves()
{
    vector<Move> all_moves = get_all_moves();
    vector<Move> valid_moves = all_moves;

    // TODO: Implement logic to filter out invalid moves

    return valid_moves;
}
