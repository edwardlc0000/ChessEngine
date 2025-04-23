#pragma once

#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include "ChessTypes.hpp"
#include "ChessBoard.hpp"
#include <vector>
#include <array>
#include <utility>
#include <string>

struct Move
{
	Piece piece;
	int from;
	int to;
	PieceType promotion;
	bool is_capture;
	bool is_en_passant;
	bool is_castling;	
	bool is_check;
};

const std::array<int, 8> KNIGHT_MOVES = { 15, 17, -15, -17, 10, -10, 6, -6 };
const std::array<int, 8> KING_MOVES = { NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST };
const std::array<int, 4> BISHOP_MOVES = { NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST };
const std::array<int, 4> ROOK_MOVES = { NORTH, SOUTH, EAST, WEST };
const std::array<int, 8> QUEEN_MOVES = { NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST };

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

	/**
	 * @brief Generates all possible attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate attacks for.
	 * @return A pair of bitboards representing the attacks for white and black pieces.
	 */
	 std::pair<Bitboard, Bitboard> generate_attacks(const ChessBoard& board);

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

	/*
	 * @brief Filters legal moves based on the current board state.
	 * 
	 * @param board The chessboard to filter moves for.
	 */
	void filter_legal_moves(const ChessBoard& board);

	/**
	 * @brief Generates pawn attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate pawn attacks for.
	 */
	std::pair<Bitboard, Bitboard> generate_pawn_attacks(const ChessBoard& board);

	/**
	 * @brief Generates knight attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate knight attacks for.
	 */
	std::pair<Bitboard, Bitboard> generate_knight_attacks(const ChessBoard& board);

	/**
	 * @brief Generates bishop attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate bishop attacks for.
	 */
	std::pair<Bitboard, Bitboard> generate_bishop_attacks(const ChessBoard& board);

	/**
	 * @brief Generates rook attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate rook attacks for.
	 */
	std::pair<Bitboard, Bitboard> generate_rook_attacks(const ChessBoard& board);

	/**
	 * @brief Generates queen attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate queen attacks for.
	 */
	std::pair<Bitboard, Bitboard> generate_queen_attacks(const ChessBoard& board);

	/**
	 * @brief Generates king attacks for the given chessboard.
	 *
	 * @param board The chessboard to generate king attacks for.
	 */
	std::pair<Bitboard, Bitboard> generate_king_attacks(const ChessBoard& board);
};
#endif // MOVEGENERATOR_HPP
