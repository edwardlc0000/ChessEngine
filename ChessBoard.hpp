#pragma once

#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "ChessTypes.hpp"
#include "Bitboard.hpp"
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class ChessBoard
{
private:
	Color active_color;
	bool white_kingside_castle;
	bool white_queenside_castle;
	bool black_kingside_castle;
	bool black_queenside_castle;
	std::string en_passant_target_square;
	int halfmove_clock;
	int fullmove_number;
public:
	std::array<Bitboard, 12> bitboards; // 0-5 for white, 6-11 for black

	/**
	 * @brief Default constructor for ChessBoard.
	 *
	 * @details Initializes the chessboard with the starting position.
	 */
	ChessBoard();

	/**
	 * @brief Constructor for ChessBoard with a given FEN string.
	 *
	 * @param fen The FEN string to initialize the chessboard with.
	 * @details This constructor allows for the creation of a ChessBoard from a specific position represented in FEN format.
	 */
	ChessBoard(const std::string& fen);

	/*
	 * @brief Initializes the chessboard with the starting position.
	 * 
	 * @details This function sets up the initial position of the chess pieces on the board.
	 */
	void init_board();

	/**
	 * @brief Initializes the chessboard with a given FEN string.
	 * 
	 * @param fen The FEN string to initialize the chessboard with.
	 * @details This function parses the FEN string and sets up the board accordingly.
	 */
	void init_fen_board(const std::string& fen);

	/*
	 * @brief Outputs the chessboard to an output stream.
	 * 
	 * @param os The output stream to write to.
	 * @param board The chessboard to output.
	 * @details This functions overloads the << operator to output the chessboard as a FEN string.
	 */
	friend std::ostream& operator<<(std::ostream& os, const ChessBoard& board);
};

#endif // CHESSBOARD_HPP