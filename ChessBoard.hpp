#pragma once

#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "ChessTypes.hpp"
#include "Bitboard.hpp"
#include "MoveGenerator.hpp"
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Precalculated bitboards for starting positions
const Bitboard WHITE_STARTING_ATTACKS = 0x000000000000FF00;
const Bitboard BLACK_STARTING_ATTACKS = 0x00FF000000000000;

class ChessBoard
{
public:
	// Current state of the board
	Color active_color;
	bool white_kingside_castle;
	bool white_queenside_castle;
	bool black_kingside_castle;
	bool black_queenside_castle;
	std::string en_passant_target_string;
	int en_passant_target_index;
	int halfmove_clock;
	int fullmove_number;

	/**
	 * Bitboards for each piece type
	 * 
	 * 0-5: White pieces
	 * 6-11: Black pieces
	 * 12: All white pieces
	 * 13: All black pieces
	 * 14: All pieces
	 * 15: Empty squares
	 */
	std::array<Bitboard, 16> bitboards;

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
	 * @brief Applies a move to the chessboard.
	 *
	 * @param move The move to apply.
	 * @details This function updates the chessboard state based on the provided move.
	 */
	void apply_move(const Move& move);

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