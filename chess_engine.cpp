// Including necessary libraries
#include <iostream>

// Using the standard namespace
using namespace std;

// Defining the data type for bitboard representation
typedef unsigned long long U64;

// Initializing bitboard variables for chess pieces
U64 white_pawns = 0xff00;
U64 white_knights = 0x42;
U64 white_bishops = 0x24;
U64 white_rooks = 0x81;
U64 white_queens = 0x8;
U64 white_king = 0x10;
U64 black_pawns = 0xff000000000000;
U64 black_knights = 0x4200000000000000;
U64 black_bishops = 0x2400000000000000;
U64 black_rooks = 0x8100000000000000;
U64 black_queens = 0x800000000000000;
U64 black_king = 0x1000000000000000;

// Function to print the bitboard representation
void print_bitboard(U64 bitboard)
{
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
        {
            cout << endl;
        }
        cout << ((bitboard >> i) & 1);
    }
    cout << endl;
}

// Main function
int main()
{
    // Printing the bitboard representation of all chess pieces
    print_bitboard(white_pawns | white_knights | white_bishops | white_rooks | white_queens | white_king | black_pawns | black_knights | black_bishops | black_rooks | black_queens | black_king);

    // Returning 0 to indicate successful execution
    return 0;
}