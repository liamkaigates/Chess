#include "game.h"

// Run the chess game loop
int runGame(SDL_Window **window, SDL_Surface **surface, unsigned long *startTime)
{
    Game game = Game();
    vector<Move> valid_moves = game.get_valid_moves();
    game.board = BitBoard();
    loadPieces(&(game.board));
    SDL_Event e;
    bool quit = false;
    pair<int, int> square;
    vector<pair<int, int>> clicks;
    unsigned long time = SDL_GetTicks();
    bool move_made = false;
    while (!quit)
    {
        drawBoard(window, surface);
        drawPieces(window, surface, &(game.board));
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
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
                    for (size_t i = 0; i < valid_moves.size(); ++i)
                    {
                        if (move == valid_moves[i])
                        {
                            game.make_move(valid_moves[i], true);
                            valid_moves = game.get_valid_moves();
                            move_made = true;
                            break;
                        }
                    }
                    if (move_made)
                    {
                        clicks.clear();
                        square = std::make_pair(-1, -1);
                        move_made = false;
                    }
                    else
                    {
                        clicks.erase(clicks.begin(), clicks.end());
                        clicks.push_back(square);
                    }
                }
            }
            else if (e.type == SDL_KEYDOWN)
            {
                SDL_Keycode keyCode = e.key.keysym.sym;
                if (keyCode == SDLK_z)
                {
                    game.undo_move();
                    valid_moves = game.get_valid_moves();
                }
            }
        }

        while (time - *startTime < 1000 / MAX_FPS)
        {
            time = SDL_GetTicks();
        }
        *startTime = time;
    }

    return 0;
}