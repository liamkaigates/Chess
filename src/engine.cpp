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
                    vector<Move> piece_moves;

                    if ((this->whiteTurn && i >= 0 && i <= 5) || (!this->whiteTurn && i >= 6 && i <= 11))
                    {
                        // Handle the case when the piece is a pawn, rook, knight, bishop, queen, or king
                        switch (i % 6)
                        {
                        case 0: // Pawn
                            piece_moves = this->get_pawn_moves(j, k);
                            break;
                        case 1: // Knight
                            piece_moves = this->get_knight_moves(j, k);
                            break;
                        case 2: // Bishop
                            piece_moves = this->get_bishop_moves(j, k);
                            break;
                        case 3: // Rook
                            piece_moves = this->get_rook_moves(j, k);
                            break;
                        case 4: // Queen
                            piece_moves = this->get_queen_moves(j, k);
                            break;
                        case 5: // King
                            piece_moves = this->get_king_moves(j, k);
                            break;
                        }
                    }

                    // Append the generated moves to the list of all moves
                    all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                }
            }
        }
    }

    return all_moves;
}

void Game::promote_pawn(int square, string piece_type)
{
    // Get the color of the pawn
    string piece = "b" + piece_type;
    if (!this->whiteTurn)
    {
        piece = "w" + piece_type;
    }

    // Get the bitboard representation of the pawn
    int pawn_index = (this->whiteTurn) ? 6 : 0;
    int promotion_index = (this->board).piece_index[piece];
    U64 &pawn_board = (this->board).boards[pawn_index];
    U64 &promotion_board = (this->board).boards[promotion_index];
    clear_bit(pawn_board, square);
    set_bit(promotion_board, square);
}

// Function to check if a square is under attack
bool Game::square_under_attack(int target_square)
{
    // Get all possible moves for the opponent
    this->whiteTurn = !this->whiteTurn;
    vector<Move> opponent_moves = get_all_moves();
    this->whiteTurn = !this->whiteTurn;

    // Check if the target square is present in the opponent's move set
    for (const Move &move : opponent_moves)
    {
        if ((move.end_file + (move.end_rank * DIMENSION)) == target_square)
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
        return square_under_attack(this->white_king_location);
    }
    else
    {
        return square_under_attack(this->black_king_location);
    }
}

// Function to get valid moves
vector<Move> Game::get_valid_moves()
{
    vector<Move> all_moves = get_all_moves();
    vector<Move> valid_moves;
    vector<int> temp_en_passant_pawns = this->en_passant_pawns;
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
        this->undo_move(false);
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
    this->en_passant_pawns = temp_en_passant_pawns;
    return valid_moves;
}
