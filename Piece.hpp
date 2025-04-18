#pragma once

#ifndef PIECE_HPP
#define PIECE_HPP

#include "ChessTypes.hpp"
#include <iostream>

class Piece
{
	private:
		Color color;
		PieceType type;

public:
	Piece(Color c, PieceType t);

	friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

};

#endif // PIECE_HPP