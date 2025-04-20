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
};

class MoveGenerator
{
public:
	/**
	 * @brief Generates all possible moves for the given chessboard.
	 *
	 * @param board The chessboard to generate moves for.
	 * @return A vector of possible moves.
	 */
	static std::vector<Move> generate_moves(const ChessBoard& board);

private:
	/**
	 * @brief Generates moves for pawns.
	 *
	 * @param board The chessboard to generate moves for.
	 * @param moves The vector to store the generated moves.
	 */
	static void generate_pawn_moves(const ChessBoard& board, std::vector<Move>& moves);

	/**
	 * @brief Generates moves for knights.
	 *
	 * @param board The chessboard to generate moves for.
	 * @param moves The vector to store the generated moves.
	 */
	static void generate_knight_moves(const ChessBoard& board, std::vector<Move>& moves);

	/**
	 * @brief Generates moves for bishops.
	 *
	 * @param board The chessboard to generate moves for.
	 * @moves The vector to store the generated moves.
	 */
	static void generate_bishop_moves(const ChessBoard& board, std::vector<Move>& moves);

	/**
	 * @brief Generates moves for rooks.
	 *
	 * @param board The chessboard to generate moves for.
	 * @moves The vector to store the generated moves.
	 */
	static void generate_rook_moves(const ChessBoard& board, std::vector<Move>& moves);

	/**
	 * @brief Generates moves for queens.
	 *
	 * @param board The chessboard to generate moves for.
	 * @moves The vector to store the generated moves.
	 */
	static void generate_queen_moves(const ChessBoard& board, std::vector<Move>& moves);

	/**
	 * @brief Generates moves for kings.
	 *
	 * @param board The chessboard to generate moves for.
	 * @moves The vector to store the generated moves.
	 */
	static void generate_king_moves(const ChessBoard& board, std::vector<Move>& moves);
};
#endif // MOVEGENERATOR_HPP
