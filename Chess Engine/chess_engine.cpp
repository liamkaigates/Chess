// Bitboard representation of chess board
typedef unsigned __int64 U64;

// Bitboard representation of chess pieces  
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

void print_bitboard(U64 bitboard) {
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((bitboard >> i) & 1);
    }
    std::cout << std::endl;
}

int main() {
    print_bitboard(white_pawns);
    print_bitboard(white_knights);
    print_bitboard(white_bishops);
    print_bitboard(white_rooks);
    print_bitboard(white_queens);
    print_bitboard(white_king);
    print_bitboard(black_pawns);
    print_bitboard(black_knights);
    print_bitboard(black_bishops);
    print_bitboard(black_rooks);
    print_bitboard(black_queens);
    print_bitboard(black_king);
    return 0;
}