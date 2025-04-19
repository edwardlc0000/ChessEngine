#include "ChessBoard.hpp"

ChessBoard::ChessBoard()
{
	init_board();
}

void ChessBoard::init_board()
{
	bitboards[WHITE_PAWN] = Bitboard(WHITE, PAWN);
	bitboards[WHITE_KNIGHT] = Bitboard(WHITE, KNIGHT);
	bitboards[WHITE_BISHOP] = Bitboard(WHITE, BISHOP);
	bitboards[WHITE_ROOK] = Bitboard(WHITE, ROOK);
	bitboards[WHITE_QUEEN] = Bitboard(WHITE, QUEEN);
	bitboards[WHITE_KING] = Bitboard(WHITE, KING);
	bitboards[BLACK_PAWN] = Bitboard(BLACK, PAWN);
	bitboards[BLACK_KNIGHT] = Bitboard(BLACK, KNIGHT);
	bitboards[BLACK_BISHOP] = Bitboard(BLACK, BISHOP);
	bitboards[BLACK_ROOK] = Bitboard(BLACK, ROOK);
	bitboards[BLACK_QUEEN] = Bitboard(BLACK, QUEEN);
	bitboards[BLACK_KING] = Bitboard(BLACK, KING);
}