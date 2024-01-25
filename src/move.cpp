// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to add a move to the list of moves
void Game::add_move(Move move)
{
    (*this).moves.push_back(move);
}

// Function to find the captured piece
char Game::find_captured_piece(int i, int j)
{
    int endSquare = i * DIMENSION + j;

    // Check each piece type on the board to see if it occupies the destination square
    for (int pieceIndex = 0; pieceIndex < 12; ++pieceIndex)
    {
        U64 board = (this->board).boards[pieceIndex];
        if (get_bit(board, endSquare) == 1)
        {
            return (this->board).piece_map[pieceIndex][1]; // Return the piece type (e.g., 'p', 'r', 'n', 'b', 'q', 'k')
        }
    }

    return '\0'; // Return null character if no piece is found
}

// Function to check if a square on the board is empty
bool Game::is_empty_square(int bit)
{
    return (get_bit(this->board.get_black_board() | this->board.get_white_board(), bit) == 0);
}

// Function to get the move based on the clicks
Move Game::get_move(vector<pair<int, int>> clicks)
{
    int square = (DIMENSION - 1 - clicks[0].first) * DIMENSION + clicks[0].second;
    Move move;
    move.start_rank = DIMENSION - 1 - clicks[0].first;
    move.start_file = clicks[0].second;
    move.end_rank = DIMENSION - 1 - clicks[1].first;
    move.end_file = clicks[1].second;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, square) == 1)
        {
            move.color = (*this).board.piece_map[i][0];
            move.piece = (*this).board.piece_map[i][1];
            return move;
        }
    }
    return move;
}

// Function to make a move
void Game::make_move(Move move, bool user)
{
    // cout << "Making move" << endl;
    // this->print_move(move);
    int startSquare = move.start_rank * DIMENSION + move.start_file;
    int endSquare = move.end_rank * DIMENSION + move.end_file;
    for (int i = 0; i < 12; ++i)
    {
        U64 &board = (this->board).boards[i];
        if (get_bit(board, startSquare) == 1)
        {
            if (i == 5)
            {
                this->white_king_location = {move.end_rank, move.end_file};
            }
            else if (i == 11)
            {
                this->black_king_location = {move.end_rank, move.end_file};
            }
            clear_bit(board, startSquare);
            clear_boards(endSquare);
            if (move.is_enpassant)
            {
                U64 &en_passant_board = (this->whiteTurn) ? (this->board).boards[6] : (this->board).boards[0];
                clear_bit(en_passant_board, (move.en_passant_file + DIMENSION * move.en_passant_rank));
            }
            if (move.piece == 'p' && abs(move.end_rank - move.start_rank) == 2)
            {
                en_passant_pawns.push_back({move.end_rank, move.end_file});
            }
            else
            {
                en_passant_pawns.push_back({-1, -1});
            }
            if (move.promotion && !user)
            {
                promote_pawn(endSquare, "q");
            }
            else
            {
                set_bit(board, endSquare);
            }
            this->add_move(move);
            this->whiteTurn = !this->whiteTurn;
            break;
        }
    }
    // if (move.piece == 'p')
    // {
    //     cout << "wp" << endl;
    //     this->print_board(board.boards[0]);
    //     cout << "bp" << endl;
    //     this->print_board(board.boards[6]);
    // }
}

// Function to undo a move
void Game::undo_move(bool user)
{
    if (!moves.empty())
    {
        // cout << "Undoing move" << endl;
        Move move = moves.back();
        // this->print_move(move);
        moves.pop_back();
        int startSquare = move.start_rank * DIMENSION + move.start_file;
        int endSquare = move.end_rank * DIMENSION + move.end_file;
        char capturedPiece = move.capture_piece;
        for (int i = 0; i < 12; ++i)
        {
            U64 &board = (*this).board.boards[i];
            if (get_bit(board, endSquare) == 1)
            {
                if (i == 5)
                {
                    this->white_king_location = {move.start_rank, move.start_file};
                }
                else if (i == 11)
                {
                    this->black_king_location = {move.start_rank, move.start_file};
                }
                clear_bit(board, endSquare);
                clear_boards(startSquare);
                if (move.is_enpassant)
                {
                    U64 &en_passant_board = (this->whiteTurn) ? (this->board).boards[0] : (this->board).boards[6];
                    set_bit(en_passant_board, (move.en_passant_file + DIMENSION * move.en_passant_rank));
                }
                en_passant_pawns.pop_back();
                if (move.promotion)
                {
                    int pawn_index = (this->whiteTurn) ? 6 : 0;
                    set_bit((this->board).boards[pawn_index], startSquare);
                }
                else
                {
                    set_bit(board, startSquare);
                }
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
                            set_bit((this->board).boards[2], endSquare);
                        break;
                    case 'q':
                        if (move.color == 'w')
                            set_bit((this->board).boards[10], endSquare);
                        else
                            set_bit((this->board).boards[4], endSquare);
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
        // if (move.piece == 'p')
        // {
        //     cout << "wp" << endl;
        //     this->print_board(board.boards[0]);
        //     cout << "bp" << endl;
        //     this->print_board(board.boards[6]);
        // }
    }
}

// Function to create a move for a piece
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

// Function to add a piece move to the list of moves
bool Game::add_piece_move(vector<Move> &moves, Move &move, U64 opposite_board, char capture_color)
{
    if (this->is_empty_square((move.end_file + DIMENSION * move.end_rank)))
    {
        move.capture = false;
        move.is_enpassant = false;
        moves.push_back(move);
    }
    else
    {
        if (get_bit(opposite_board, (move.end_file + DIMENSION * move.end_rank)) == 1)
        {
            move.capture = true;
            move.capture_piece = this->find_captured_piece(move.end_rank, move.end_file);
            move.capture_color = capture_color;
            move.is_enpassant = false;
            moves.push_back(move);
        }
        return true;
    }
    return false;
}
