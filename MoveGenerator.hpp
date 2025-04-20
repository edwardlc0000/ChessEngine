#pragma once

#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include "ChessTypes.hpp"
#include "ChessBoard.hpp"
#include <vector>
#include <string>

struct Move
{
	int from;
	int to;
	PieceType promotion;
	bool is_castling;
	bool is_en_passant;
	bool is_capture;
	bool is_check;
};

class MoveGenerator
{
public:
	std::vector<Move> all_moves; // List of generated moves
	std::vector<Move> tactical_moves; // List of tactical moves

	/**
	 * @brief Generates all possible moves for the given chessboard.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_all_moves(const ChessBoard& board);

	/**
	 * @brief Generates tactical moves for the given chessboard.
	 * 
	 * @param board The chessboard to generate tactical moves for.
	 */
	void generate_tactical_moves(const ChessBoard& board);

private:
	/**
	 * @brief Generates moves for pawns.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_pawn_moves(const ChessBoard& board);

	/**
	 * @brief Generates moves for knights.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_knight_moves(const ChessBoard& board);

	/**
	 * @brief Generates moves for bishops.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_bishop_moves(const ChessBoard& board);

	/**
	 * @brief Generates moves for rooks.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_rook_moves(const ChessBoard& board);

	/**
	 * @brief Generates moves for queens.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_queen_moves(const ChessBoard& board);

	/**
	 * @brief Generates moves for kings.
	 *
	 * @param board The chessboard to generate moves for.
	 */
	void generate_king_moves(const ChessBoard& board);
};
#endif // MOVEGENERATOR_HPP
