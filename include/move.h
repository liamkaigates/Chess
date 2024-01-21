// Move class represents a chess move
class Move
{
public:
    char piece;         // The piece being moved
    char color;         // The color of the piece
    int start_file;     // The starting file of the move
    int start_rank;     // The starting rank of the move
    int end_file;       // The ending file of the move
    int end_rank;       // The ending rank of the move
    bool capture;       // Indicates if a capture is made during the move
    char capture_piece; // The captured piece, if any
    char capture_color; // The color of the captured piece, if any
    bool promotion;     // Indicates if a pawn promotion occurs during the move

    // Define the equality operator
    bool operator==(const Move &other) const
    {
        // Compare the attributes of the moves
        return piece == other.piece &&
               color == other.color &&
               start_file == other.start_file &&
               start_rank == other.start_rank &&
               end_file == other.end_file &&
               end_rank == other.end_rank;
    }
};