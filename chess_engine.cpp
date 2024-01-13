// Including necessary libraries
#include <iostream>
#include <chess.h>

// Using the standard namespace
using namespace std;

class Game
{
public:
    BitBoard board;
    bool whiteTurn = true;
    bool white_castle = true;
    bool black_castle = true;
    vector<Move> moves;
};