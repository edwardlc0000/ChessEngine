#include "Piece.hpp"
#include <string>

Piece::Piece(Color c, PieceType t)
{
	color = c;
	type = t;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
	std::string piece_str;
	if (piece.color == WHITE)
	{
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
	}
	else
	{
		switch (piece.type)
		{
		case PAWN: piece_str = "p"; break;
		case KNIGHT: piece_str = "n"; break;
		case BISHOP: piece_str = "b"; break;
		case ROOK: piece_str = "r"; break;
		case QUEEN: piece_str = "q"; break;
		case KING: piece_str = "k"; break;
		default: piece_str = ""; break;
		}
	}
	os << piece_str;
	return os;
}
