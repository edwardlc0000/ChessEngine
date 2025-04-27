#include "MoveGenerator.hpp"

MoveGenerator::MoveGenerator()
{
	// Initialize the moves vector
	all_moves.reserve(256); // Reserve space for 256 moves to avoid multiple allocations
	tactical_moves.reserve(256); // Reserve space for 256 tactical moves
}

void MoveGenerator::generate_all_moves(const ChessBoard& board)
{
	all_moves.clear(); // Clear previous moves
	generate_pawn_moves(board);
	generate_knight_moves(board);
	generate_bishop_moves(board);
	generate_rook_moves(board);
	generate_queen_moves(board);
	generate_king_moves(board);
}

void MoveGenerator::generate_tactical_moves(const ChessBoard& board)
{
	generate_all_moves(board);
	tactical_moves.clear();
	for (const Move& move : all_moves)
	{
		if (move.is_capture || move.is_check || move.promotion != NONE)
		{
			tactical_moves.push_back(move);
		}
	}
}

void MoveGenerator::generate_attacks(const ChessBoard& board)
{
	attacks.fill(Bitboard(0));
	generate_pawn_attacks(board);
	generate_knight_attacks(board);
	generate_bishop_attacks(board);
	generate_rook_attacks(board);
	generate_queen_attacks(board);
	generate_king_attacks(board);
}

void MoveGenerator::generate_pawn_moves(const ChessBoard& board)
{
	Bitboard pawns = board.bitboards[board.active_color == WHITE ? WHITE_PAWN : BLACK_PAWN];
	Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];
	Piece piece = board.active_color == WHITE ? WHITE_PAWN : BLACK_PAWN;

	while (pawns.board)
	{
		int from = pawns.get_LSB();
		pawns.pop_LSB();

		int to = board.active_color == WHITE ? from + NORTH : from + SOUTH;

		// Non-capture moves
		if (board.bitboards[EMPTY].get_bit(to))
		{
			if ((board.active_color == WHITE && to == RANK_8) ||
				(board.active_color == BLACK && to == RANK_1))
			{
				// Promotion moves
				for (int promotion = KNIGHT; promotion <= QUEEN; promotion++)
				{
					Move move = { piece, from, to, static_cast<PieceType>(promotion), false, false, false, false };
					all_moves.push_back(move);
				}
			}
			else
			{
				// Single push
				Move move = { piece, from, to, NONE, false, false, false, false };
				all_moves.push_back(move);

				// Double push
				if ((board.active_color == WHITE && to == RANK_2) ||
					(board.active_color == BLACK && to == RANK_7))
				{
					int double_to = board.active_color == WHITE ? to + NORTH : to + SOUTH;
					if (board.bitboards[EMPTY].get_bit(double_to))
					{
						Move double_move = { piece, from, double_to, NONE, false, false, false, false };
						all_moves.push_back(double_move);
					}
				}
			}
		}

		// Capture moves
		int capture_west = board.active_color == WHITE ? from + NORTH_WEST : from + SOUTH_WEST;
		int capture_east = board.active_color == WHITE ? from + NORTH_EAST : from + SOUTH_EAST;

		// Ensure capture_west does not wrap around the west edge
		if (from % 8 != 0 && hostile_pieces.get_bit(capture_west)) // Not on File A
		{
			Move capture_move = { piece, from, capture_west, NONE, true, false, false, false };
			all_moves.push_back(capture_move);
		}

		// Ensure capture_east does not wrap around the east edge
		if (from % 8 != 7 && hostile_pieces.get_bit(capture_east)) // Not on File H
		{
			Move capture_move = { piece, from, capture_east, NONE, true, false, false, false };
			all_moves.push_back(capture_move);
		}

		// En passant
		if (board.en_passant_target_index == capture_west || board.en_passant_target_index == capture_east)
		{
			Move en_passant_move = { piece, from, board.en_passant_target_index, NONE, false, true, false, false };
			all_moves.push_back(en_passant_move);
		}
	}
}

void MoveGenerator::generate_knight_moves(const ChessBoard& board)
{
	Bitboard knights = board.bitboards[board.active_color == WHITE ? WHITE_KNIGHT : BLACK_KNIGHT];
	Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];
	Piece piece = board.active_color == WHITE ? WHITE_KNIGHT : BLACK_KNIGHT;

	while (knights.board)
	{
		int from = knights.get_LSB();
		int from_file = from % 8;
		knights.pop_LSB();
		for (int i = 0; i < 8; i++)
		{
			int to = from + KNIGHT_MOVES[i];
			// Ensure to is within bounds
			if (to < 0 || to >= 64) continue;
			// Ensure to does not wrap around the edges
			int to_file = to % 8;
			if (abs(from_file - to_file) > 2) continue;

			if (board.bitboards[EMPTY].get_bit(to))
			{
				// Normal move
				Move move = { piece, from, to, NONE, false, false, false, false };
				all_moves.push_back(move);
			}
			else if (hostile_pieces.get_bit(to))
			{
				// Capture move
				Move capture_move = { piece, from, to, NONE, true, false, false, false };
				all_moves.push_back(capture_move);
			}
			
		}
	}
}

void MoveGenerator::generate_bishop_moves(const ChessBoard& board)
{
	Bitboard bishops = board.bitboards[board.active_color == WHITE ? WHITE_BISHOP : BLACK_BISHOP];
	Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];
	Piece piece = board.active_color == WHITE ? WHITE_BISHOP : BLACK_BISHOP;

	while (bishops.board)
	{
		int from = bishops.get_LSB();
		bishops.pop_LSB();
		for (int i = 0; i < 4; i++)
		{
			int to = from;
			while (true)
			{
				int from_rank = to / 8;
				int from_file = to % 8;
				to += BISHOP_MOVES[i];
				// Ensure to is within bounds
				if (to < 0 || to >= 64) break;
				// Ensure to does not wrap around the edges
				int to_rank = to / 8;
				int to_file = to % 8;
				if (abs(from_file - to_file) > 1 && abs(from_rank - to_rank) > 1) break;
				if (board.bitboards[EMPTY].get_bit(to))
				{
					// Normal move
					Move move = { piece, from, to, NONE, false, false, false, false };
					all_moves.push_back(move);
				}
				else if (hostile_pieces.get_bit(to))
				{
					// Capture move
					Move capture_move = { piece, from, to, NONE, true, false, false, false };
					all_moves.push_back(capture_move);
					break; // Stop after capturing
				}
				else
				{
					break; // Blocked by friendly piece
				}
			}
		}
	}
}

void MoveGenerator::generate_rook_moves(const ChessBoard& board)
{
	Bitboard rooks = board.bitboards[board.active_color == WHITE ? WHITE_ROOK : BLACK_ROOK];
	Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];
	Piece piece = board.active_color == WHITE ? WHITE_ROOK : BLACK_ROOK;

	while (rooks.board)
	{
		int from = rooks.get_LSB();
		rooks.pop_LSB();
		for (int i = 0; i < 4; i++)
		{
			int to = from;
			while (true)
			{
				to += ROOK_MOVES[i];
				// Ensure to is within bounds
				if (to < 0 || to >= 64) break;
				// Ensure to does not wrap around the edges
				if (from / 8 != to / 8) break;
				if (board.bitboards[EMPTY].get_bit(to))
				{
					// Normal move
					Move move = { piece, from, to, NONE, false, false, false, false };
					all_moves.push_back(move);
				}
				else if (hostile_pieces.get_bit(to))
				{
					// Capture move
					Move capture_move = { piece, from, to, NONE, true, false, false, false };
					all_moves.push_back(capture_move);
					break; // Stop after capturing
				}
				else
				{
					break; // Blocked by friendly piece
				}
			}
		}
	}
}

void MoveGenerator::generate_queen_moves(const ChessBoard& board)
{
	Bitboard queens = board.bitboards[board.active_color == WHITE ? WHITE_QUEEN : BLACK_QUEEN];
	Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];
	Piece piece = board.active_color == WHITE ? WHITE_QUEEN : BLACK_QUEEN;

	while (queens.board)
	{
		int from = queens.get_LSB();
		queens.pop_LSB();
		for (int i = 0; i < 8; i++)
		{
			int to = from;
			int from_rank = to / 8;
			int from_file = to % 8;
			while (true)
			{
				to += QUEEN_MOVES[i];
				// Ensure to is within bounds
				if (to < 0 || to >= 64) break;
				// Ensure to does not wrap around the edges
				int to_rank = to / 8;
				int to_file = to % 8;
				if (abs(from_file - to_file) > 1 && abs(from_rank - to_rank) > 1) break;
				if (board.bitboards[EMPTY].get_bit(to))
				{
					// Normal move
					Move move = { piece, from, to, NONE, false, false, false, false };
					all_moves.push_back(move);
				}
				else if (hostile_pieces.get_bit(to))
				{
					// Capture move
					Move capture_move = { piece, from, to, NONE, true, false, false, false };
					all_moves.push_back(capture_move);
					break; // Stop after capturing
				}
				else
				{
					break; // Blocked by friendly piece
				}
			}
		}
	}
}

void MoveGenerator::generate_king_moves(const ChessBoard& board)
{
	Bitboard king = board.bitboards[board.active_color == WHITE ? WHITE_KING : BLACK_KING];
	Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];
	Piece piece = board.active_color == WHITE ? WHITE_KING : BLACK_KING;

	while (king.board)
	{
		int from = king.get_LSB();
		int from_file = from % 8;
		king.pop_LSB();
		for (int i = 0; i < 8; i++)
		{
			int to = from + KING_MOVES[i];
			// Ensure to is within bounds
			if (to < 0 || to >= 64) continue;
			// Ensure to does not wrap around the edges
			int to_file = to % 8;
			if (abs(from_file - to_file) > 1) continue;
			if (board.bitboards[EMPTY].get_bit(to))
			{
				// Normal move
				Move move = { piece, from, to, NONE, false, false, false, false };
				all_moves.push_back(move);
			}
			else if (hostile_pieces.get_bit(to))
			{
				// Capture move
				Move capture_move = { piece, from, to, NONE, true, false, false, false };
				all_moves.push_back(capture_move);
			}
		}
	}
}

void MoveGenerator::generate_pawn_attacks(const ChessBoard& board)
{
	Bitboard white_pawns = board.bitboards[WHITE_PAWN];
	Bitboard black_pawns = board.bitboards[BLACK_PAWN];

	//Prevent wrap around for white pawns
	Bitboard white_pawns_not_on_file_a = white_pawns & ~Bitboard(FILE_A);
	Bitboard white_pawns_not_on_file_h = white_pawns & ~Bitboard(FILE_H);

	attacks[WHITE_PAWN] = (white_pawns_not_on_file_a << 7) | (white_pawns_not_on_file_h << 9);


	//Prevent wrap around for black pawns
	Bitboard black_pawns_not_on_file_a = black_pawns & ~Bitboard(FILE_A);
	Bitboard black_pawns_not_on_file_h = black_pawns & ~Bitboard(FILE_H);

	attacks[BLACK_PAWN] = (black_pawns_not_on_file_h >> 7) | (black_pawns_not_on_file_a >> 9);
}

void MoveGenerator::generate_knight_attacks(const ChessBoard& board)
{
	Bitboard white_knights = board.bitboards[WHITE_KNIGHT];
	Bitboard black_knights = board.bitboards[BLACK_KNIGHT];

	while (white_knights.board)
	{
		int from = white_knights.get_LSB();
		int from_file = from % 8;
		white_knights.pop_LSB();
		for (int i = 0; i < 8; i++)
		{
			int to = from + KNIGHT_MOVES[i];
			int to_file = to % 8;
			if (to < 0 || to >= 64) continue;
			// Ensure to does not wrap around the edges
			if (abs(from_file - to_file) > 2) continue;
			attacks[WHITE_KNIGHT].set_bit(to);
		}
	}

	while (black_knights.board)
	{
		int from = black_knights.get_LSB();
		int from_file = from % 8;
		black_knights.pop_LSB();
		for (int i = 0; i < 8; i++)
		{
			int to = from + KNIGHT_MOVES[i];
			int to_file = to % 8;
			if (to < 0 || to >= 64) continue;
			// Ensure to does not wrap around the edges
			if (abs(from_file - to_file) > 2) continue;
			attacks[BLACK_KNIGHT].set_bit(to);
		}
	}
}

void MoveGenerator::generate_bishop_attacks(const ChessBoard& board)
{
	Bitboard white_bishops = board.bitboards[WHITE_BISHOP];
	Bitboard black_bishops = board.bitboards[BLACK_BISHOP];

	while (white_bishops.board)
	{
		int from = white_bishops.get_LSB();
		white_bishops.pop_LSB();
		for (int i = 0; i < 4; i++)
		{
			int to = from;
			while (true)
			{
				int from_rank = to / 8;
				int from_file = to % 8;
				to += BISHOP_MOVES[i];
				// Ensure to is within bounds
				if (to < 0 || to >= 64) break;
				// Ensure to does not wrap around the edges
				int to_rank = to / 8;
				int to_file = to % 8;
				if (abs(from_file - to_file) > 1 && abs(from_rank - to_rank) > 1) break;
				if (board.bitboards[EMPTY].get_bit(to))
				{
					attacks[WHITE_BISHOP].set_bit(to);
				}
				else if (board.bitboards[BLACK_PIECES].get_bit(to))
				{
					attacks[WHITE_BISHOP].set_bit(to);
				}
				else
				{
					attacks[WHITE_BISHOP].set_bit(to);
					break; // Blocked by friendly piece
				}
			}
		}
	}

	while (black_bishops.board)
	{
		int from = black_bishops.get_LSB();
		black_bishops.pop_LSB();
		for (int i = 0; i < 4; i++)
		{
			int to = from;
			while (true)
			{
				int from_rank = to / 8;
				int from_file = to % 8;
				to += BISHOP_MOVES[i];
				// Ensure to is within bounds
				if (to < 0 || to >= 64) break;
				// Ensure to does not wrap around the edges
				int to_rank = to / 8;
				int to_file = to % 8;
				if (abs(from_file - to_file) > 1 && abs(from_rank - to_rank) > 1) break;
				if (board.bitboards[EMPTY].get_bit(to))
				{
					attacks[BLACK_BISHOP].set_bit(to);
				}
				else if (board.bitboards[WHITE_PIECES].get_bit(to))
				{
					attacks[BLACK_BISHOP].set_bit(to);
				}
				else
				{
					attacks[BLACK_BISHOP].set_bit(to);
					break; // Blocked by friendly piece
				}
			}
		}
	}
}

void MoveGenerator::generate_rook_attacks(const ChessBoard& board)
{
	Bitboard white_rooks = board.bitboards[WHITE_ROOK];
	Bitboard black_rooks = board.bitboards[BLACK_ROOK];
}

void MoveGenerator::generate_queen_attacks(const ChessBoard& board)
{
	Bitboard white_queens = board.bitboards[WHITE_QUEEN];
	Bitboard black_queens = board.bitboards[BLACK_QUEEN];
}

void MoveGenerator::generate_king_attacks(const ChessBoard& board)
{
	Bitboard white_king = board.bitboards[WHITE_KING];
	Bitboard black_king = board.bitboards[BLACK_KING];

	int from = white_king.get_LSB();
	int from_file = from % 8;
	for (int i = 0; i < 8; i++)
	{		
		int to = from + KING_MOVES[i];
		int to_file = to % 8;

		// Ensure to is within bounds
		if (to < 0 || to >= 64) continue;
		// Ensure to does not wrap around the edges
		if (abs(from_file - to_file) > 1) continue;
		attacks[WHITE_KING].set_bit(to);
	}

	from = black_king.get_LSB();
	from_file = from % 8;
	for (int i = 0; i < 0; i++)
	{
		int to = from + KING_MOVES[i];
		int to_file = to % 8;

		// Ensure to is within bounds
		if (to < 0 || to >= 64) continue;
		// Ensure to does not wrap around the edges
		if (abs(from_file - to_file) > 1) continue;
		attacks[BLACK_KING].set_bit(to);
	}
}