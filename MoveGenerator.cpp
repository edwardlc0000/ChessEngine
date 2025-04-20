#include "MoveGenerator.hpp"

MoveGenerator::MoveGenerator()
{
	// Initialize the moves vector
	all_moves.reserve(256); // Reserve space for 256 moves to avoid multiple allocations
	tactical_moves.reserve(256); // Reserve space for 256 tactical moves
}

void MoveGenerator::generate_all_moves(const ChessBoard& board)
{
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

void MoveGenerator::generate_pawn_moves(const ChessBoard& board)
{
	Bitboard pawns = board.bitboards[board.active_color == WHITE ? WHITE_PAWN : BLACK_PAWN];

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
					Move move = { from, to, static_cast<PieceType>(promotion), false, false };
					all_moves.push_back(move);
				}
			}
			else
			{
				// Single push
				Move move = { from, to, NONE, false, false };
				all_moves.push_back(move);

				// Double push
				if ((board.active_color == WHITE && to == RANK_2) ||
					(board.active_color == BLACK && to == RANK_7))
				{
					int double_to = board.active_color == WHITE ? to + NORTH : to + SOUTH;
					if (board.bitboards[EMPTY].get_bit(double_to))
					{
						Move double_move = { from, double_to, NONE, false, false };
						all_moves.push_back(double_move);
					}
				}
			}
		}

		// Capture moves
		int capture_west = board.active_color == WHITE ? from + NORTH_WEST : from + SOUTH_WEST;
		int capture_east = board.active_color == WHITE ? from + NORTH_EAST : from + SOUTH_EAST;

		Bitboard hostile_pieces = board.bitboards[board.active_color == WHITE ? BLACK_PIECES : WHITE_PIECES];

		// Ensure capture_west does not wrap around the west edge
		if (from % 8 != 0 && hostile_pieces.get_bit(capture_west)) // Not on File A
		{
			Move capture_move = { from, capture_west, NONE, false, false, true };
			all_moves.push_back(capture_move);
		}

		// Ensure capture_east does not wrap around the east edge
		if (from % 8 != 7 && hostile_pieces.get_bit(capture_east)) // Not on File H
		{
			Move capture_move = { from, capture_east, NONE, false, false, true };
			all_moves.push_back(capture_move);
		}
	}
}

void MoveGenerator::generate_knight_moves(const ChessBoard& board)
{
	Bitboard knights = board.bitboards[board.active_color == WHITE ? WHITE_KNIGHT : BLACK_KNIGHT];
}

void MoveGenerator::generate_bishop_moves(const ChessBoard& board)
{
	Bitboard bishops = board.bitboards[board.active_color == WHITE ? WHITE_BISHOP : BLACK_BISHOP];
}

void MoveGenerator::generate_rook_moves(const ChessBoard& board)
{
	Bitboard rooks = board.bitboards[board.active_color == WHITE ? WHITE_ROOK : BLACK_ROOK];
}

void MoveGenerator::generate_queen_moves(const ChessBoard& board)
{
	Bitboard queens = board.bitboards[board.active_color == WHITE ? WHITE_QUEEN : BLACK_QUEEN];
}

void MoveGenerator::generate_king_moves(const ChessBoard& board)
{
	Bitboard king = board.bitboards[board.active_color == WHITE ? WHITE_KING : BLACK_KING];
}