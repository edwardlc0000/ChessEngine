#pragma once

#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "ChessTypes.hpp"
#include "Bitboard.hpp"
#include <array>

class ChessBoard
{
private:
	
public:
	std::array<Bitboard, 12> bitboards; // 0-5 for white, 6-11 for black

	/**
	 * @brief Default constructor for ChessBoard.
	 *
	 * @details Initializes the chessboard with the starting position.
	 */
	ChessBoard();

	/*
	 * @brief
	 */
	void init_board();
};

#endif // CHESSBOARD_HPP