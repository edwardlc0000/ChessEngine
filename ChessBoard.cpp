#include "ChessBoard.hpp"

ChessBoard::ChessBoard()
{
	init_board();
}

ChessBoard::ChessBoard(const std::string& fen)
{
	init_fen_board(fen);
}

void ChessBoard::init_board()
{
	// Initialize the bitboards for each piece type
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

	// Set the state of the initial position
	active_color = WHITE;
	white_kingside_castle = true;
	white_queenside_castle = true;
	black_kingside_castle = true;
	black_queenside_castle = true;
	en_passant_target_square = "";
	halfmove_clock = 0;
	fullmove_number = 1;
}

void ChessBoard::init_fen_board(const std::string& fen)
{

}