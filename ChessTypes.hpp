#pragma once

#ifndef CHESSTYPES_HPP
#define CHESSTYPES_HPP

#include <cstdint>
#include <string>

typedef uint64_t U64;

enum Color
{
	WHITE = 8,
	BLACK = 16,
};

enum PieceType
{
	NONE,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
};

#endif // CHESSTYPES_HPP
