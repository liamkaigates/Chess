#include <gtest/gtest.h>
#include "game.h"
#include "engine.h"
#include <cstdlib> // Include the necessary header for rand() function

using namespace std;

class ChessAppTest : public ::testing::Test
{
public:
    void checkNoMissingPieces(Game game, const BitBoard &original_board, const Move &move);
    void checkPiecesRestored(Game game, const BitBoard &original_board, const Move &move);

protected:
    virtual void SetUp()
    {
        // Code to be executed before each test case
        // Initialize SDL or any other necessary setup
    }

    virtual void TearDown()
    {
        // Code to be executed after each test case
        // Clean up SDL or any other resources
    }
};

// Helper function to check no missing pieces after a move
void ChessAppTest::checkNoMissingPieces(Game game, const BitBoard &original_board, const Move &move)
{
    int start_square = move.start_rank * DIMENSION + move.start_file;
    int end_square = move.end_rank * DIMENSION + move.end_file;

    // Ensure no missing pieces after the move
    for (int pieceType = 0; pieceType < 12; ++pieceType)
    {
        U64 *pieceBoard = &(game.board.boards[pieceType]);
        U64 pieces = *pieceBoard;

        for (int i = 0; i < DIMENSION; ++i)
        {
            for (int j = 0; j < DIMENSION; ++j)
            {
                int square = i * DIMENSION + j;
                if (square != start_square && square != end_square)
                    ASSERT_EQ(get_bit(pieces, square), get_bit(original_board.boards[pieceType], square)) << "Piece missing after making a move";
            }
        }
    }
}

// Helper function to check pieces are restored after undoing a move
void ChessAppTest::checkPiecesRestored(Game game, const BitBoard &original_board, const Move &move)
{
    int start_square = move.start_rank * DIMENSION + move.start_file;
    int end_square = move.end_rank * DIMENSION + move.end_file;

    // Ensure pieces are restored after undo
    for (int pieceType = 0; pieceType < 12; ++pieceType)
    {
        U64 *pieceBoard = &(game.board.boards[pieceType]);
        U64 pieces = *pieceBoard;

        for (int i = 0; i < DIMENSION; ++i)
        {
            for (int j = 0; j < DIMENSION; ++j)
            {
                int square = i * DIMENSION + j;
                if (square != start_square && square != end_square)
                    ASSERT_EQ(get_bit(pieces, square), get_bit(original_board.boards[pieceType], square)) << "Piece missing after making a move";
            }
        }
    }
}

// Test initialization of the game
TEST_F(ChessAppTest, GameInitialization)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    // Add more checks if needed
}

// Test the drawing of the chessboard
TEST_F(ChessAppTest, DrawChessboard)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    // Assuming SQ_SIZE, DIMENSION, and other constants are defined
    ASSERT_EQ(drawBoard(&renderer), 0) << "Failed to draw the chessboard";

    // Add more checks if needed
}

// Test loading chess piece images
TEST_F(ChessAppTest, LoadChessPieces)
{

    BitBoard bitboard;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    ASSERT_EQ(loadPieces(&bitboard, &renderer), 0) << "Failed to load chess piece images";

    // Add more checks if needed
}

// Test making a move in the chess game
TEST_F(ChessAppTest, MakeChessMove)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    Game game;
    game.board = BitBoard();
    ASSERT_EQ(loadPieces(&(game.board), &renderer), 0) << "Failed to load chess piece images";

    // Assuming valid_moves and other necessary variables are available
    vector<Move> valid_moves = game.get_valid_moves();
    ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

    Move move = valid_moves[0]; // Select the first valid move

    ASSERT_NO_THROW(game.make_move(move, true)) << "Failed to make a move";

    // Add more checks if needed
}

// Test undoing a move in the chess game
TEST_F(ChessAppTest, UndoChessMove)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    Game game;
    game.board = BitBoard();
    ASSERT_EQ(loadPieces(&(game.board), &renderer), 0) << "Failed to load chess piece images";

    // Make a move
    vector<Move> valid_moves = game.get_valid_moves();
    ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

    Move move = valid_moves[0];
    ASSERT_NO_THROW(game.make_move(move, true)) << "Failed to make a move";

    // Undo the move
    ASSERT_NO_THROW(game.undo_move()) << "Failed to undo the move";

    // Add more checks if needed
}

// Test making multiple random moves and ensuring no missing pieces
TEST_F(ChessAppTest, MakeMultipleRandomMovesNoMissingPieces)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    Game game;
    game.board = BitBoard();
    ASSERT_EQ(loadPieces(&(game.board), &renderer), 0) << "Failed to load chess piece images";

    // Assuming valid_moves and other necessary variables are available
    vector<Move> valid_moves;

    // Make multiple random moves
    for (int i = 0; i < 20; ++i) // Adjust the number of random moves as needed
    {
        valid_moves = game.get_valid_moves();
        ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

        // Select a random valid move
        Move move = valid_moves[rand() % valid_moves.size()];

        // Store the state before making a move
        BitBoard original_board = game.board;

        // Make the random move
        ASSERT_NO_THROW(game.make_move(move, true)) << "Failed to make a move";

        // Ensure no missing pieces after the move
        checkNoMissingPieces(game, original_board, move);
    }
}

// Test undoing multiple random moves and ensuring pieces are restored
TEST_F(ChessAppTest, UndoMultipleRandomMovesRestorePieces)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &renderer, &time), 0) << "SDL initialization failed";

    Game game;
    game.board = BitBoard();
    ASSERT_EQ(loadPieces(&(game.board), &renderer), 0) << "Failed to load chess piece images";
    int start_square;
    int end_square;
    // Assuming valid_moves and other necessary variables are available
    vector<Move> valid_moves;

    // Store the state before undoing the moves
    BitBoard original_board = game.board;

    // Make multiple random moves
    for (int i = 0; i < 20; ++i) // Adjust the number of random moves as needed
    {
        valid_moves = game.get_valid_moves();
        ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

        // Select a random valid move
        Move move = valid_moves[rand() % valid_moves.size()];

        // Make the random move
        ASSERT_NO_THROW(game.make_move(move, true)) << "Failed to make a move";
        start_square = move.start_rank * DIMENSION + move.start_file;
        end_square = move.end_rank * DIMENSION + move.end_file;
    }

    // Undo multiple random moves
    for (int i = 0; i < 20; ++i) // Adjust the number of random moves as needed
    {
        ASSERT_NO_THROW(game.undo_move()) << "Failed to undo the move";
    }
    // Ensure pieces are restored after undoing multiple moves
    for (int pieceType = 0; pieceType < 12; ++pieceType)
    {
        U64 *pieceBoard = &(game.board.boards[pieceType]);
        U64 pieces = *pieceBoard;

        for (int i = 0; i < DIMENSION; ++i)
        {
            for (int j = 0; j < DIMENSION; ++j)
            {
                int square = i * DIMENSION + j;
                if (square != start_square && square != end_square)
                    ASSERT_EQ(get_bit(pieces, square), get_bit(original_board.boards[pieceType], square)) << "Piece missing after making a move";
            }
        }
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
