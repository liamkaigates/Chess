#include <gtest/gtest.h>
#include "game.h"
#include "sdl_helper.h"

using namespace std;

class ChessAppTest : public ::testing::Test
{
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

// Add more test cases as needed

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
