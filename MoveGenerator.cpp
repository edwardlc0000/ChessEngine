#include "MoveGenerator.hpp"

std::vector<Move> MoveGenerator::generate_moves(const ChessBoard& board)
{
	std::vector<Move> moves;

	generate_pawn_moves(board, moves);
	generate_knight_moves(board, moves);
	generate_bishop_moves(board, moves);
	generate_rook_moves(board, moves);
	generate_queen_moves(board, moves);
	generate_king_moves(board, moves);
	return moves;
}

void MoveGenerator::generate_pawn_moves(const ChessBoard& board, std::vector<Move>& moves)
{
	Bitboard pawns = board.bitboards[board.active_color == WHITE ? WHITE_PAWN : BLACK_PAWN];

	while (pawns.board)
	{
		int from = pawns.get_LSB();
		pawns.pop_LSB();

		int to = board.active_color == WHITE ? from + NORTH : from + SOUTH;

		if (board.bitboards[EMPTY].get_bit(to))
		{
			Move move = { from, to, NONE, false, false };
			moves.push_back(move);

			if ((board.active_color == WHITE && to == RANK_2) ||
				(board.active_color == BLACK && to == RANK_7))
			{
				int double_to = board.active_color == WHITE ? to + NORTH : to + SOUTH;
				if (board.bitboards[EMPTY].get_bit(double_to))
				{
					Move double_move = { from, double_to, NONE, false, false };
					moves.push_back(double_move);
				}
			}
		}
	}
}

void MoveGenerator::generate_knight_moves(const ChessBoard& board, std::vector<Move>& moves)
{
	Bitboard knights = board.bitboards[board.active_color == WHITE ? WHITE_KNIGHT : BLACK_KNIGHT];
}

void MoveGenerator::generate_bishop_moves(const ChessBoard& board, std::vector<Move>& moves)
{
	Bitboard bishops = board.bitboards[board.active_color == WHITE ? WHITE_BISHOP : BLACK_BISHOP];
}

void MoveGenerator::generate_rook_moves(const ChessBoard& board, std::vector<Move>& moves)
{
	Bitboard rooks = board.bitboards[board.active_color == WHITE ? WHITE_ROOK : BLACK_ROOK];
}

void MoveGenerator::generate_queen_moves(const ChessBoard& board, std::vector<Move>& moves)
{
	Bitboard queens = board.bitboards[board.active_color == WHITE ? WHITE_QUEEN : BLACK_QUEEN];
}

void MoveGenerator::generate_king_moves(const ChessBoard& board, std::vector<Move>& moves)
{
	Bitboard king = board.bitboards[board.active_color == WHITE ? WHITE_KING : BLACK_KING];
}