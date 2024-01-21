TEST_F(ChessAppTest, MakeChessMove)
{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &surface, &time), 0) << "SDL initialization failed";

    Game game;
    game.board = BitBoard();
    loadPieces(&(game.board));

    // Assuming valid_moves and other necessary variables are available
    vector<Move> valid_moves = game.get_valid_moves();
    ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

    Move move = valid_moves[0]; // Select the first valid move

    ASSERT_NO_THROW(game.make_move(move, true)) << "Failed to make a move";

    // Add more checks if needed
}

// FILEPATH: /Users/liamgates/Desktop/Chess/Chess/test/test.cpp
TEST_F(ChessAppTest, InitSDL)
{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    unsigned long time;

    ASSERT_EQ(init(&window, &surface, &time), 0) << "SDL initialization failed";

    // Add more checks if needed
}

// FILEPATH: /Users/liamgates/Desktop/Chess/Chess/test/test.cpp
TEST_F(ChessAppTest, LoadPieces)
{
    Game game;
    game.board = BitBoard();

    ASSERT_NO_THROW(loadPieces(&(game.board))) << "Failed to load pieces";

    // Add more checks if needed
}

// FILEPATH: /Users/liamgates/Desktop/Chess/Chess/test/test.cpp
TEST_F(ChessAppTest, GetValidMoves)
{
    Game game;
    game.board = BitBoard();
    loadPieces(&(game.board));

    vector<Move> valid_moves = game.get_valid_moves();

    ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

    // Add more checks if needed
}

// FILEPATH: /Users/liamgates/Desktop/Chess/Chess/test/test.cpp
TEST_F(ChessAppTest, MakeMove)
{
    Game game;
    game.board = BitBoard();
    loadPieces(&(game.board));

    // Assuming valid_moves and other necessary variables are available
    vector<Move> valid_moves = game.get_valid_moves();
    ASSERT_GT(static_cast<size_t>(valid_moves.size()), (size_t)0) << "No valid moves available";

    Move move = valid_moves[0]; // Select the first valid move

    ASSERT_NO_THROW(game.make_move(move, true)) << "Failed to make a move";

    // Add more checks if needed
}