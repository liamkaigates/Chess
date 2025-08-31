#include "sdl_helper.h"

// Initialize SDL
int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() < 0)
    {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
    }

    *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SQ_SIZE * DIMENSION, SQ_SIZE * DIMENSION, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        cout << "Error creating SDL Window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Try to create a hardware-accelerated renderer first
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL)
    {
        // Fall back to software renderer (useful for headless CI with dummy video driver)
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
        if (*renderer == NULL)
        {
            cout << "Error creating SDL Renderer: " << SDL_GetError() << endl;
            SDL_DestroyWindow(*window);
            SDL_Quit();
            return -1;
        }
    }

    return 0;
}

// Draw the chessboard
int drawBoard(SDL_Renderer **renderer)
{
    SDL_SetRenderDrawColor(*renderer, 238, 238, 210, 255);
    SDL_RenderClear(*renderer);
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            SDL_Rect rect = {i * SQ_SIZE, j * SQ_SIZE, SQ_SIZE, SQ_SIZE};
            if ((i + j) % 2 == 0)
            {
                SDL_SetRenderDrawColor(*renderer, 238, 238, 210, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(*renderer, 118, 150, 86, 255);
            }
            SDL_RenderFillRect(*renderer, &rect);
        }
    }
    return 0;
}

// Load chess piece images
int loadPieces(BitBoard *bitboard, SDL_Renderer **renderer)
{
    string piece_path[] = {"wp", "wn", "wb", "wr", "wq", "wk", "bp", "bn", "bb", "br", "bq", "bk"};
    for (int i = 0; i < 12; ++i)
    {
        string path = "piece_images/" + piece_path[i] + ".bmp";
        SDL_Surface *piece = SDL_LoadBMP(path.c_str());
        if (piece == NULL)
        {
            printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return -1;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, piece);
        if (texture == NULL)
        {
            printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
            SDL_FreeSurface(piece);
            return -1;
        }
        SDL_FreeSurface(piece);
        bitboard->image_map[piece_path[i]] = texture;
    }
    return 0;
}

// Draw chess pieces on the board
int drawPieces(SDL_Renderer **renderer, BitBoard *bitboard)
{
    string piece_path[] = {"wp", "wn", "wb", "wr", "wq", "wk", "bp", "bn", "bb", "br", "bq", "bk"};
    for (int i = 0; i < 12; ++i)
    {
        U64 board = bitboard->boards[i];
        for (int j = 0; j < DIMENSION; ++j)
        {
            for (int k = 0; k < DIMENSION; ++k)
            {
                if (get_bit(board, (j * DIMENSION + k)) == 1)
                {
                    SDL_Rect rect = {k * SQ_SIZE, (DIMENSION - 1 - j) * SQ_SIZE, SQ_SIZE, SQ_SIZE};
                    SDL_RenderCopy(*renderer, bitboard->image_map[piece_path[i]], NULL, &rect);
                }
            }
        }
    }

    return 0;
}

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void highlight_valid_squares(SDL_Renderer *renderer, vector<Move> validMoves, pair<int, int> square)
{
    if (square != make_pair(-1, -1))
    {
        int r = square.first;
        int c = square.second;
        // Draw the circle on valid squares
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        // Set color of square
        SDL_SetRenderDrawColor(renderer, 235, 97, 80, 50);
        // Highlight start square
        SDL_RenderFillRect(renderer, new SDL_Rect{c * SQ_SIZE, r * SQ_SIZE, SQ_SIZE, SQ_SIZE});

        for (const Move &move : validMoves)
        {
            if ((DIMENSION - 1 - move.start_rank) == r && move.start_file == c)
            {
                // Draw the circle on valid squares
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                // Draw a semi-transparent circle
                draw_circle(renderer, SQ_SIZE * move.end_file + SQ_SIZE / 2, SQ_SIZE * (DIMENSION - 1 - move.end_rank) + SQ_SIZE / 2, SQ_SIZE / 6, {0, 0, 0, 50});
            }
        }
    }
}

int animate(SDL_Renderer **renderer, Game game, Move move)
{
    float row;
    float col;
    float row_diff = move.end_rank - move.start_rank;
    float col_diff = move.end_file - move.start_file;
    float frames = (abs(row_diff) + abs(col_diff)) * 10;
    for (int i = 0; i <= frames; ++i)
    {
        row = ((DIMENSION - 1 - move.start_rank) - row_diff * i / frames) * (float)SQ_SIZE;
        col = (move.start_file + col_diff * i / frames) * (float)SQ_SIZE;
        drawBoard(renderer);
        drawPieces(renderer, &(game.board));

        SDL_Rect rect = {move.end_file * SQ_SIZE, (DIMENSION - 1 - move.end_rank) * SQ_SIZE, SQ_SIZE, SQ_SIZE};
        if ((move.end_file + move.end_rank) % 2 == 1)
        {
            SDL_SetRenderDrawColor(*renderer, 238, 238, 210, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(*renderer, 118, 150, 86, 255);
        }
        SDL_RenderFillRect(*renderer, &rect);
        if (move.capture)
        {
            string capture = {move.capture_color, move.capture_piece};
            if (move.is_enpassant)
            {
                SDL_Rect capture_rect = {move.end_file * SQ_SIZE, (DIMENSION - 1 - move.start_rank) * SQ_SIZE, SQ_SIZE, SQ_SIZE};
                SDL_RenderCopy(*renderer, game.board.image_map[capture], NULL, &capture_rect);
            }
            else
            {
                SDL_Rect capture_rect = {move.end_file * SQ_SIZE, (DIMENSION - 1 - move.end_rank) * SQ_SIZE, SQ_SIZE, SQ_SIZE};
                SDL_RenderCopy(*renderer, game.board.image_map[capture], NULL, &capture_rect);
            }
        }

        string piece = {move.color, move.piece};
        SDL_Rect piece_rect = {(int)col, (int)row, SQ_SIZE, SQ_SIZE};
        SDL_RenderCopy(*renderer, game.board.image_map[piece], NULL, &piece_rect);
        SDL_RenderPresent(*renderer);
        SDL_Delay(250 / frames);
    }

    return 0;
}

// Function to display the winner at the end of the game
void endgame(SDL_Renderer **renderer, Game &game, bool checkmate)
{
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Rect textRect;
    SDL_Rect background = {(int)(1.5 * SQ_SIZE), (int)(SQ_SIZE * 3), SQ_SIZE * 5, SQ_SIZE};
    textRect.x = (int)(SQ_SIZE * 1.75);
    textRect.y = (int)(SQ_SIZE * 3.25);
    SDL_Surface *textSurface = nullptr;
    SDL_Texture *textTexture = nullptr;

    string text;

    if (checkmate && game.whiteTurn)
    {
        text = "Black wins by checkmate!";
    }
    else if (checkmate && !game.whiteTurn)
    {
        text = "White wins by checkmate!";
    }
    else
    {
        text = "           Stalemate!           ";
    }

    // Use your preferred font and size
    TTF_Font *font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 24);

    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        // Handle font loading error
    }

    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (!textSurface)
    {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        // Handle text rendering error
    }

    textTexture = SDL_CreateTextureFromSurface(*renderer, textSurface);

    if (!textTexture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        // Handle texture creation error
    }

    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderFillRect(*renderer, &background);
    SDL_RenderCopy(*renderer, textTexture, NULL, &textRect);

    // Cleanup
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

// Close the SDL window and clean up
int close(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
