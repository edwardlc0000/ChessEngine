#include "Bitboard.hpp"

Bitboard::Bitboard()
{
	board = 0;
}

Bitboard::Bitboard(U64 b)
{
	board = b;
}

Bitboard::Bitboard(const Bitboard& b)
{
	board = b.board;
}

Bitboard::Bitboard(Color c, PieceType t)
{
	board = 0;
	switch (t)
	{
		case PAWN: board = 0x00FF000000000000; break;
		case KNIGHT: board = 0x0000000000000042; break;
		case BISHOP: board = 0x0000000000000024; break;
		case ROOK: board = 0x0000000000000081; break;
		case QUEEN: board = 0x0000000000000008; break;
		case KING: board = 0x0000000000000010; break;
		default: break;
	}
	if (c == BLACK) board <<= 48;
}

void Bitboard::set_bit(int index)
{
	if (index < 0 || index > 63)
	{
		throw std::out_of_range("Index must be between 0 and 63.");
	}
	board |= (1ULL << index);
}

void Bitboard::clear_bit(int index)
{
	if (index < 0 || index > 63)
	{
		throw std::out_of_range("Index must be between 0 and 63.");
	}
	board &= ~(1ULL << index);
}

int Bitboard::get_bit(int index) const
{
	if (index < 0 || index > 63)
	{
		throw std::out_of_range("Index must be between 0 and 63.");
	}
	return (board >> index) & 1;
}

int Bitboard::get_LSB() const
{
	if (board == 0)
	{
		throw std::runtime_error("Bitboard is uninitialized or empty.");
	}
	return __builtin_ctzll(board);
}

int Bitboard::pop_LSB()
{
	if (board == 0)
	{
		throw std::runtime_error("Bitboard is uninitialized or empty.");
	}
	int lsb_index = get_LSB();
	board &= (board - 1);
	return lsb_index;
}