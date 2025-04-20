#pragma once

#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include "ChessTypes.hpp"
#include <iostream>
#include <bitset>
#include <stdexcept>

class Bitboard
{	
public:
	U64 board;

	/**
	 * @brief Default constructor for Bitboard.
	 * 
	 * @details Initializes the board to 0.
	 */
	Bitboard();

	/**
	 * @brief Constructor for Bitboard with a given U64 value.
	 *
	 * @param b The U64 value to initialize the board with.
	 * @details This constructor allows for the creation of a Bitboard with a specific bit pattern.
	 */
	Bitboard(U64 b);

	/**
	 * @brief Copy constructor for Bitboard.
	 * 
	 * @param b The Bitboard to copy.
	 * @details This constructor creates a new Bitboard that is a copy of the provided Bitboard.
	 */
	Bitboard(const Bitboard& b);

	/**
	 * @brief Constructor for bitboard with a color and piece type.
	 * 
	 * @param c The color of the piece.
	 * @param t The type of the piece.
	 * @details This constructor initializes the bitboard with a specific piece type and color.
	 */
	Bitboard(Color c, PieceType t);

	/**
	 * @brief Sets a specific bit in the bitboard.
	 * 
	 * @param index The index of the bit to set (0-63).
	 * @throws std::out_of_range if the index is out of bounds (not between 0 and 63).
	 */
	void set_bit(int index);

	/**
	 * @brief Clears a specific bit in the bitboard.
	 * 
	 * @param index The index of the bit to clear (0-63).
	 * @throws std::out_of_range if the index is out of bounds (not between 0 and 63).
	 */
	void clear_bit(int index);

	/**
	 * @brief Gets the value of the bit at a specific index.
	 *
	 * @param index The index of the bit to get (0-63).
	 * @return The value of the bit at the specified index (0 or 1).
	 * @throws std::out_of_range if the index is out of bounds (not between 0 and 63).
	 */
	int get_bit(int index) const;

	/**
	 * @brief Gets the index of the least significant bit (LSB) that is set to 1.
	 * 
	 * @return The index of the LSB (0-63).
	 * @throws std::runtime_error if the bitboard is empty (all bits are 0).
	 */
	int get_LSB() const;

	/**
	 * @brief Pops the least significant bit (LSB) from the bitboard.
	 * 
	 * @return The index of the LSB (0-63).
	 * @throws std::runtime_error if the bitboard is empty (all bits are 0).
	 */
	int pop_LSB();

	/**
	 * @brief Bitwise NOT operation on the bitboard.
	 */
	Bitboard operator~() const;

	/**
	 * @brief Bitwise AND operation between two bitboards.
	 * 
	 * @param other The other bitboard to AND with.
	 * @return A new Bitboard that is the result of the AND operation.
	 */
	Bitboard operator&(const Bitboard& other) const;

	/**
	 * @brief Bitwise OR operation between two bitboards.
	 * 
	 * @param other The other bitboard to OR with.
	 * @return A new Bitboard that is the result of the OR operation.
	 */
	Bitboard operator|(const Bitboard& other) const;

	/**
	 * @brief Bitwise XOR operation between two bitboards.
	 *
	 * @param other The other bitboard to XOR with.
	 * @return A new Bitboard that is the result of the XOR operation.
	 */
	Bitboard operator^(const Bitboard& other) const;
};

#endif // !BITBOARD_HPP
