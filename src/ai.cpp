#include <ai.h>

Move AI::random_move(vector<Move> valid_moves)
{
    int random_index = rand() % valid_moves.size();
    return valid_moves[random_index];
}