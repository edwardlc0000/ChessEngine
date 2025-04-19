#pragma once

#ifndef PIECE_HPP
#define PIECE_HPP

#include "ChessTypes.hpp"
#include "Bitboard.hpp"
#include <iostream>
#include <string>
#include <cctype>

class Piece
{
	private:
		Color color;
		PieceType type;
		Bitboard bitboard;

public:
	Piece(Color c, PieceType t);

	friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

};

#endif // PIECE_HPP