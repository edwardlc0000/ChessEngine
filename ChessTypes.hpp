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
	KING,
	NONE
};

enum PieceValue
{
	PAWN_VALUE = 100,
	KNIGHT_VALUE = 300,
	BISHOP_VALUE = 300,
	ROOK_VALUE = 500,
	QUEEN_VALUE = 900,
	KING_VALUE = 0
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

const U64 FILE_A = 0x0101010101010101;
const U64 FILE_B = FILE_A << 1;
const U64 FILE_C = FILE_B << 1;
const U64 FILE_D = FILE_C << 1;
const U64 FILE_E = FILE_D << 1;
const U64 FILE_F = FILE_E << 1;
const U64 FILE_G = FILE_F << 1;
const U64 FILE_H = FILE_G << 1;

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
