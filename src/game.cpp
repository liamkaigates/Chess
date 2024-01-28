#include "game.h"

// Run the chess game loop
int runGame(SDL_Renderer **renderer)
{
    Game game = Game();
    game.castle_right = 15;
    game.castle_rights.push_back(game.castle_right);
    vector<Move> valid_moves = game.get_valid_moves();
    cout << "Getting valid moves" << endl;
    game.print_moves(valid_moves);
    game.board = BitBoard();
    loadPieces(&(game.board), renderer);
    SDL_Event e;
    bool quit = false;
    bool promotion = false;
    bool animation = false;
    int promotion_square = 0;
    pair<int, int> square = make_pair(-1, -1);
    vector<pair<int, int>> clicks;
    bool move_made = false;
    bool game_over = false;
    while (!quit)
    {
        drawBoard(renderer);
        highlight_valid_squares(*renderer, valid_moves, square);
        drawPieces(renderer, &(game.board));
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && !game_over)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int col = x / SQ_SIZE;
                int row = y / SQ_SIZE;
                if (square == std::make_pair(row, col) || col >= 8 || row >= 8)
                {
                    square = std::make_pair(-1, -1);
                    clicks.clear();
                }
                else
                {
                    square = std::make_pair(row, col);
                    clicks.push_back(square);
                }
                if (clicks.size() == 2)
                {
                    Move move = game.get_move(clicks);
                    cout << "Getting valid moves" << endl;
                    game.print_moves(valid_moves);
                    for (size_t i = 0; i < valid_moves.size(); ++i)
                    {
                        if (move == valid_moves[i])
                        {
                            // cout << "User made move" << endl;
                            // game.print_move(valid_moves[i]);
                            game.make_move(valid_moves[i], true);
                            if (valid_moves[i].promotion)
                            {
                                promotion = true;
                                promotion_square = move.end_file + DIMENSION * move.end_rank;
                            }
                            valid_moves = game.get_valid_moves();
                            move_made = true;
                            animation = true;
                            break;
                        }
                    }
                }
            }
            else if (e.type == SDL_KEYDOWN)
            {
                SDL_Keycode keyCode = e.key.keysym.sym;
                if (keyCode == SDLK_z)
                {
                    game.undo_move(true);
                    valid_moves = game.get_valid_moves();
                    animation = false;
                }
                else if (keyCode == SDLK_r)
                {
                    game = Game();
                    game.castle_right = 15;
                    game.castle_rights.push_back(game.castle_right);
                    valid_moves = game.get_valid_moves();
                    game.board = BitBoard();
                    loadPieces(&(game.board), renderer);
                    promotion = false;
                    animation = false;
                    game_over = false;
                    promotion_square = 0;
                    square = {-1, -1};
                    clicks.clear();
                    move_made = false;
                }
            }
        }
        if (move_made)
        {
            if (animation)
                animate(renderer, game, game.moves[game.moves.size() - 1]);
            clicks.clear();
            square = std::make_pair(-1, -1);
            move_made = false;
            animation = false;
        }
        else
        {
            clicks.erase(clicks.begin(), clicks.end());
            clicks.push_back(square);
        }
        if (game.checkmate)
        {
            game_over = true;
            endgame(renderer, game, true);
        }
        else if (game.stalemate)
        {
            game_over = true;
            endgame(renderer, game, false);
        }
        while (promotion)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    SDL_Keycode keyCode = e.key.keysym.sym;
                    if (keyCode == SDLK_q)
                    {
                        game.promote_pawn(promotion_square, "q");
                        promotion = false;
                        valid_moves = game.get_valid_moves();
                        promotion_square = 0;
                    }
                    else if (keyCode == SDLK_r)
                    {
                        game.promote_pawn(promotion_square, "r");
                        promotion = false;
                        valid_moves = game.get_valid_moves();
                        promotion_square = 0;
                    }
                    else if (keyCode == SDLK_b)
                    {
                        game.promote_pawn(promotion_square, "b");
                        promotion = false;
                        valid_moves = game.get_valid_moves();
                        promotion_square = 0;
                    }
                    else if (keyCode == SDLK_n)
                    {
                        game.promote_pawn(promotion_square, "n");
                        promotion = false;
                        valid_moves = game.get_valid_moves();
                        promotion_square = 0;
                    }
                }
            }
        }
        SDL_RenderPresent(*renderer);
    }
    return 0;
}