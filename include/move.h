#ifndef MOVE_H
#define MOVE_H

// Move class represents a chess move
class Move
{
public:
    char piece;          // The piece being moved
    char color;          // The color of the piece
    int start_file;      // The starting file of the move
    int start_rank;      // The starting rank of the move
    int end_file;        // The ending file of the move
    int end_rank;        // The ending rank of the move
    bool capture;        // Indicates if a capture is made during the move
    char capture_piece;  // The captured piece, if any
    char capture_color;  // The color of the captured piece, if any
    bool promotion;      // Indicates if a pawn promotion occurs during the move
    bool is_enpassant;   // Indicates if the move is an en passant capture
    int en_passant_file; // The file of the en passant capture
    int en_passant_rank; // The rank of the en passant capture

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

#endif // MOVE_H