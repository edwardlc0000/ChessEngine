#include "Piece.hpp"

Piece::Piece(Color c, PieceType t)
{
	color = c;
	type = t;
	bitboard = Bitboard(c, t);
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
	std::string piece_str;
	switch (piece.type)
	{
		case PAWN: piece_str = "P"; break;
		case KNIGHT: piece_str = "N"; break;
		case BISHOP: piece_str = "B"; break;
		case ROOK: piece_str = "R"; break;
		case QUEEN: piece_str = "Q"; break;
		case KING: piece_str = "K"; break;
		default: piece_str = ""; break;
	}
	if (piece.color == BLACK) piece_str = std::tolower(piece_str[0]);
	os << piece_str;
	return os;
}
