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
		case PAWN:    board = (c == WHITE) ? 0x000000000000FF00 : 0x00FF000000000000; break;
		case KNIGHT:  board = (c == WHITE) ? 0x0000000000000042 : 0x4200000000000000; break;
		case BISHOP:  board = (c == WHITE) ? 0x0000000000000024 : 0x2400000000000000; break;
		case ROOK:    board = (c == WHITE) ? 0x0000000000000081 : 0x8100000000000000; break;
		case QUEEN:   board = (c == WHITE) ? 0x0000000000000008 : 0x0800000000000000; break;
		case KING:    board = (c == WHITE) ? 0x0000000000000010 : 0x1000000000000000; break;
		default: break;
	}
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

	#ifdef _MSC_VER
		unsigned long index;
		_BitScanForward64(&index, board);
		return static_cast<int>(index);
	#else
		return __builtin_ctzll(board);
	#endif
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

Bitboard Bitboard::operator~() const
{
	return Bitboard(~board);
}

Bitboard Bitboard::operator&(const Bitboard& other) const
{
	return Bitboard(board & other.board);
}

Bitboard Bitboard::operator|(const Bitboard& other) const
{
	return Bitboard(board | other.board);
}

Bitboard Bitboard::operator^(const Bitboard& other) const
{
	return Bitboard(board ^ other.board);
}

Bitboard Bitboard::Bitboard::operator<<(int shift) const
{
	return Bitboard(board << shift);
}

Bitboard Bitboard::operator>>(int shift) const
{
	return Bitboard(board >> shift);
}

Bitboard Bitboard::operator&=(const Bitboard& other)
{
	return board &= other.board;
}

Bitboard Bitboard::operator|=(const Bitboard& other)
{
	return board |= other.board;
}