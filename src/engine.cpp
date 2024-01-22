// Including necessary libraries
#include <engine.h>

// Using the standard namespace
using namespace std;

// Function to get all possible moves for all pieces on the board
vector<Move> Game::get_all_moves()
{
    vector<Move> all_moves;

    // Iterate through all pieces on the board
    for (int i = 0; i < 12; ++i)
    {
        U64 board = (this->board).boards[i];

        // Iterate through each square on the board
        for (int j = 0; j < DIMENSION; ++j)
        {
            for (int k = 0; k < DIMENSION; ++k)
            {
                // Check if the current square contains a piece
                if (get_bit(board, (j * DIMENSION + k)) == 1)
                {
                    string piece = (this->board).piece_map[i];

                    // Generate moves based on the type of piece and the current turn
                    if (piece == "wp" && this->whiteTurn)
                    {
                        // Handle the case when the piece is a white pawn
                        vector<Move> pawn_moves = this->get_pawn_moves(j, k);
                        all_moves.insert(all_moves.end(), pawn_moves.begin(), pawn_moves.end());
                    }
                    else if (piece == "wr" && this->whiteTurn)
                    {
                        // Handle the case when the piece is a white rook
                        vector<Move> rook_moves = this->get_rook_moves(j, k);
                        all_moves.insert(all_moves.end(), rook_moves.begin(), rook_moves.end());
                    }
                    else if (piece == "wn" && this->whiteTurn)
                    {
                        // Handle the case when the piece is a white knight
                        vector<Move> knight_moves = this->get_knight_moves(j, k);
                        all_moves.insert(all_moves.end(), knight_moves.begin(), knight_moves.end());
                    }
                    else if (piece == "wb" && this->whiteTurn)
                    {
                        // Handle the case when the piece is a white bishop
                        vector<Move> bishop_moves = this->get_bishop_moves(j, k);
                        all_moves.insert(all_moves.end(), bishop_moves.begin(), bishop_moves.end());
                    }
                    else if (piece == "wq" && this->whiteTurn)
                    {
                        // Handle the case when the piece is a white queen
                        vector<Move> queen_moves = this->get_queen_moves(j, k);
                        all_moves.insert(all_moves.end(), queen_moves.begin(), queen_moves.end());
                    }
                    else if (piece == "wk" && this->whiteTurn)
                    {
                        // Handle the case when the piece is a white king
                        vector<Move> king_moves = this->get_king_moves(j, k);
                        all_moves.insert(all_moves.end(), king_moves.begin(), king_moves.end());
                    }
                    else if (piece == "bp" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is a black pawn
                        vector<Move> pawn_moves = this->get_pawn_moves(j, k);
                        all_moves.insert(all_moves.end(), pawn_moves.begin(), pawn_moves.end());
                    }
                    else if (piece == "br" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is a black rook
                        vector<Move> rook_moves = this->get_rook_moves(j, k);
                        all_moves.insert(all_moves.end(), rook_moves.begin(), rook_moves.end());
                    }
                    else if (piece == "bn" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is a black knight
                        vector<Move> knight_moves = this->get_knight_moves(j, k);
                        all_moves.insert(all_moves.end(), knight_moves.begin(), knight_moves.end());
                    }
                    else if (piece == "bb" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is a black bishop
                        vector<Move> bishop_moves = this->get_bishop_moves(j, k);
                        all_moves.insert(all_moves.end(), bishop_moves.begin(), bishop_moves.end());
                    }
                    else if (piece == "bq" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is a black queen
                        vector<Move> queen_moves = this->get_queen_moves(j, k);
                        all_moves.insert(all_moves.end(), queen_moves.begin(), queen_moves.end());
                    }
                    else if (piece == "bk" && !(this->whiteTurn))
                    {
                        // Handle the case when the piece is a black king
                        vector<Move> king_moves = this->get_king_moves(j, k);
                        all_moves.insert(all_moves.end(), king_moves.begin(), king_moves.end());
                    }
                }
            }
        }
    }
    return all_moves;
}

// Function to check if a square is under attack
bool Game::square_under_attack(int target_rank, int target_file)
{
    // Get all possible moves for the opponent
    this->whiteTurn = !this->whiteTurn;
    vector<Move> opponent_moves = get_all_moves();
    this->whiteTurn = !this->whiteTurn;
    // Check if the target square is present in the opponent's move set
    for (const Move &move : opponent_moves)
    {
        if (move.end_rank == target_rank && move.end_file == target_file)
        {
            return true;
        }
    }
    return false;
}

// Function to check if the current player is in check
bool Game::in_check()
{
    if (this->whiteTurn)
    {
        return square_under_attack(this->white_king_location.first, this->white_king_location.second);
    }
    else
    {
        return square_under_attack(this->black_king_location.first, this->black_king_location.second);
    }
}

// Function to get valid moves
vector<Move> Game::get_valid_moves()
{
    vector<Move> all_moves = get_all_moves();
    vector<Move> valid_moves;

    // Loop through all moves and check if the move is valid
    for (const Move &move : all_moves)
    {
        this->make_move(move, false);
        this->whiteTurn = !this->whiteTurn;

        if (!this->in_check())
        {
            valid_moves.push_back(move);
        }

        this->whiteTurn = !this->whiteTurn;
        this->undo_move();
    }

    // Check for checkmate or stalemate
    if (valid_moves.empty())
    {
        if (this->in_check())
        {
            this->checkmate = true;
        }
        else
        {
            this->stalemate = true;
        }
    }
    else
    {
        this->checkmate = false;
        this->stalemate = false;
    }
    return valid_moves;
}
