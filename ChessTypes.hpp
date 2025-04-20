#pragma once

#ifndef CHESSTYPES_HPP
#define CHESSTYPES_HPP

#include <cstdint>
#include <string>

typedef uint64_t U64;

enum Color
{
	WHITE = 0,
	BLACK = 6,
};

enum PieceType
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};

enum Piece
{
	WHITE_PAWN = WHITE + PAWN,
	WHITE_KNIGHT = WHITE + KNIGHT,
	WHITE_BISHOP = WHITE + BISHOP,
	WHITE_ROOK = WHITE + ROOK,
	WHITE_QUEEN = WHITE + QUEEN,
	WHITE_KING = WHITE + KING,
	BLACK_PAWN = BLACK + PAWN,
	BLACK_KNIGHT = BLACK + KNIGHT,
	BLACK_BISHOP = BLACK + BISHOP,
	BLACK_ROOK = BLACK + ROOK,
	BLACK_QUEEN = BLACK + QUEEN,
	BLACK_KING = BLACK + KING,
	WHITE_PIECES,
	BLACK_PIECES,
	ALL_PIECES,
	EMPTY
};

const U64 A_FILE = 0x0101010101010101;
const U64 B_FILE = A_FILE << 1;
const U64 C_FILE = B_FILE << 1;
const U64 D_FILE = C_FILE << 1;
const U64 E_FILE = D_FILE << 1;
const U64 F_FILE = E_FILE << 1;
const U64 G_FILE = F_FILE << 1;
const U64 H_FILE = G_FILE << 1;

const U64 RANK_1 = 0x00000000000000FF;
const U64 RANK_2 = RANK_1 << 8;
const U64 RANK_3 = RANK_2 << 8;
const U64 RANK_4 = RANK_3 << 8;
const U64 RANK_5 = RANK_4 << 8;
const U64 RANK_6 = RANK_5 << 8;
const U64 RANK_7 = RANK_6 << 8;
const U64 RANK_8 = RANK_7 << 8;

const int NORTH = 8;
const int NORTH_EAST = 9;
const int EAST = 1;
const int SOUTH_EAST = -7;
const int SOUTH = -8;
const int SOUTH_WEST = -9;
const int WEST = -1;
const int NORTH_WEST = 7;

#endif // CHESSTYPES_HPP
