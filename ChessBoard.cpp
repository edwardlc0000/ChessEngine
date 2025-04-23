#include "ChessBoard.hpp"

ChessBoard::ChessBoard()
{
	init_board();
}

ChessBoard::ChessBoard(const std::string& fen)
{
	init_fen_board(fen);
}

void ChessBoard::init_board()
{
	// Initialize the bitboards for each piece type
	bitboards[WHITE_PAWN] = Bitboard(WHITE, PAWN);
	bitboards[WHITE_KNIGHT] = Bitboard(WHITE, KNIGHT);
	bitboards[WHITE_BISHOP] = Bitboard(WHITE, BISHOP);
	bitboards[WHITE_ROOK] = Bitboard(WHITE, ROOK);
	bitboards[WHITE_QUEEN] = Bitboard(WHITE, QUEEN);
	bitboards[WHITE_KING] = Bitboard(WHITE, KING);
	bitboards[BLACK_PAWN] = Bitboard(BLACK, PAWN);
	bitboards[BLACK_KNIGHT] = Bitboard(BLACK, KNIGHT);
	bitboards[BLACK_BISHOP] = Bitboard(BLACK, BISHOP);
	bitboards[BLACK_ROOK] = Bitboard(BLACK, ROOK);
	bitboards[BLACK_QUEEN] = Bitboard(BLACK, QUEEN);
	bitboards[BLACK_KING] = Bitboard(BLACK, KING);

	// Set the bitboards for all pieces
	bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] | bitboards[WHITE_BISHOP] |
		bitboards[WHITE_ROOK] | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];
	bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] | bitboards[BLACK_BISHOP] |
		bitboards[BLACK_ROOK] | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];
	bitboards[ALL_PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];
	bitboards[EMPTY] = ~bitboards[ALL_PIECES];

	// Set the state of the initial position
	active_color = WHITE;
	white_kingside_castle = true;
	white_queenside_castle = true;
	black_kingside_castle = true;
	black_queenside_castle = true;
	en_passant_target_string = "";
	halfmove_clock = 0;
	fullmove_number = 1;
}

void ChessBoard::init_fen_board(const std::string& fen)
{
	// Parse the FEN string
	std::stringstream fen_stream(fen);
	std::string piece_placement, active_color_str, castling_availability, en_passant_target_square_str;
	int halfmove_clock_str, fullmove_number_str;
	std::getline(fen_stream, piece_placement, ' ');
	std::getline(fen_stream, active_color_str, ' ');
	std::getline(fen_stream, castling_availability, ' ');
	std::getline(fen_stream, en_passant_target_square_str, ' ');
	fen_stream >> halfmove_clock_str;
	fen_stream >> fullmove_number_str;

	// Initialize the bitboards for each piece type
	bitboards[WHITE_PAWN] = Bitboard();
	bitboards[WHITE_KNIGHT] = Bitboard();
	bitboards[WHITE_PAWN] = Bitboard();
	bitboards[WHITE_KNIGHT] = Bitboard();
	bitboards[WHITE_BISHOP] = Bitboard();
	bitboards[WHITE_ROOK] = Bitboard();
	bitboards[WHITE_QUEEN] = Bitboard();
	bitboards[WHITE_KING] = Bitboard();
	bitboards[BLACK_PAWN] = Bitboard();
	bitboards[BLACK_KNIGHT] = Bitboard();
	bitboards[BLACK_BISHOP] = Bitboard();
	bitboards[BLACK_ROOK] = Bitboard();
	bitboards[BLACK_QUEEN] = Bitboard();
	bitboards[BLACK_KING] = Bitboard();

	// Set the state of the board from the FEN string
	active_color = (active_color_str == "w") ? WHITE : BLACK;
	white_kingside_castle = (castling_availability.find('K') != std::string::npos);
	white_queenside_castle = (castling_availability.find('Q') != std::string::npos);
	black_kingside_castle = (castling_availability.find('k') != std::string::npos);
	black_queenside_castle = (castling_availability.find('q') != std::string::npos);
	en_passant_target_string = en_passant_target_square_str;
	halfmove_clock = halfmove_clock_str;
	fullmove_number = fullmove_number_str;

	// Parse the piece placement string
	for (int rank = 7; rank >= 0; rank--)
	{
		for (int file = 0; file < 8; file++)
		{
			int square_index = rank * 8 + file;
			char piece_char = piece_placement[square_index];
			switch (piece_char)
			{
				case 'P': bitboards[WHITE_PAWN].set_bit(square_index); break;
				case 'N': bitboards[WHITE_KNIGHT].set_bit(square_index); break;
				case 'B': bitboards[WHITE_BISHOP].set_bit(square_index); break;
				case 'R': bitboards[WHITE_ROOK].set_bit(square_index); break;
				case 'Q': bitboards[WHITE_QUEEN].set_bit(square_index); break;
				case 'K': bitboards[WHITE_KING].set_bit(square_index); break;
				case 'p': bitboards[BLACK_PAWN].set_bit(square_index); break;
				case 'n': bitboards[BLACK_KNIGHT].set_bit(square_index); break;
				case 'b': bitboards[BLACK_BISHOP].set_bit(square_index); break;
				case 'r': bitboards[BLACK_ROOK].set_bit(square_index); break;
				case 'q': bitboards[BLACK_QUEEN].set_bit(square_index); break;
				case 'k': bitboards[BLACK_KING].set_bit(square_index); break;
				default: break; // Empty square or invalid character
			}
		}
	}

	// Set the bitboards for all pieces
	bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] | bitboards[WHITE_BISHOP] |
		bitboards[WHITE_ROOK] | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];
	bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] | bitboards[BLACK_BISHOP] |
		bitboards[BLACK_ROOK] | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];
	bitboards[ALL_PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];
	bitboards[EMPTY] = ~bitboards[ALL_PIECES];
}

void ChessBoard::apply_move(const Move& move)
{
	// Update the bitboards based on the move
	bitboards[move.piece].clear_bit(move.from);
	bitboards[move.piece].set_bit(move.to);

	// Update the bitboards for all pieces
	bitboards[active_color == WHITE ? WHITE_PIECES : BLACK_PIECES].clear_bit(move.from);
	bitboards[active_color == WHITE ? WHITE_PIECES : BLACK_PIECES].set_bit(move.to);
	bitboards[ALL_PIECES].clear_bit(move.from);
	bitboards[ALL_PIECES].set_bit(move.to);

	// Update the castling rights
	if (move.piece == (active_color == WHITE ? WHITE_KING : BLACK_KING))
	{
		if (active_color == WHITE)
		{
			white_kingside_castle = false;
			white_queenside_castle = false;
		}
		else
		{
			black_kingside_castle = false;
			black_queenside_castle = false;
		}
	}
	else if (move.piece == (active_color == WHITE ? WHITE_ROOK : BLACK_ROOK))
	{
		if (move.from == (active_color == WHITE ? 0 : 56)) // Queenside rook
		{
			if (active_color == WHITE)
				white_queenside_castle = false;
			else
				black_queenside_castle = false;
		}
		else if (move.from == (active_color == WHITE ? 7 : 63)) // Kingside rook
		{
			if (active_color == WHITE)
				white_kingside_castle = false;
			else
				black_kingside_castle = false;
		}
	}

	// Update the bitboards for non-capture moves
	if (!move.is_capture)
	{
		bitboards[EMPTY].set_bit(move.from);
		bitboards[EMPTY].clear_bit(move.to);

	}

	// Update the bitboards for capture moves
	if (move.is_capture)
	{
		int hostile_piece = (active_color == WHITE) ? hostile_piece = 6 : hostile_piece = 0;
		for (int i = 0; i < 6; i++)
		{
			if (bitboards[hostile_piece + i].get_bit(move.to))
			{
				bitboards[hostile_piece + i].clear_bit(move.to);
				(active_color == WHITE) ? bitboards[BLACK_PIECES].clear_bit(move.to) : bitboards[WHITE_PIECES].clear_bit(move.to);					break;
			}
		}
	}
	if (move.is_en_passant)
	{
		bitboards[active_color == WHITE ? BLACK_PAWN : WHITE_PAWN].clear_bit(en_passant_target_index);
		bitboards[active_color == WHITE ? BLACK_PIECES : WHITE_PIECES].clear_bit(en_passant_target_index);
	}

	// Update the en passant target square
	if (move.piece == (active_color == WHITE ? WHITE_PAWN : BLACK_PAWN) && abs(move.from - move.to) == 16)
	{
		en_passant_target_index = (active_color == WHITE) ? move.to - 8 : move.to + 8;
		en_passant_target_string = std::to_string(en_passant_target_index / 8) + std::to_string(en_passant_target_index % 8);
	}
	else
	{
		en_passant_target_index = -1;
		en_passant_target_string = "";
	}

	// Update the halfmove clock
	if (move.is_capture || move.piece == (active_color == WHITE ? WHITE_PAWN : BLACK_PAWN))
	{
		halfmove_clock = 0;
	}
	else
	{
		halfmove_clock++;
	}

	// Update the fullmove number
	if (active_color == BLACK)
	{
		fullmove_number++;
	}

	// Update the active color
	active_color = (active_color == WHITE) ? BLACK : WHITE;
}

std::ostream& operator<<(std::ostream& os, const ChessBoard& board)
{
	for (int rank = 7; rank >= 0; rank--)
	{
		int empty_count = 0;
		for (int file = 0; file < 8; file++)
		{
			char piece_char;
			int square_index = rank * 8 + file;
			for (int i = 0; i < 12; i++)
			{
				if (board.bitboards[i].get_bit(square_index))
				{
					PieceType piece_type = static_cast<PieceType>(i % 6);
					Color color = static_cast<Color>(i / 6);

					switch (piece_type)
					{
						case PAWN: piece_char = (color == WHITE) ? 'P' : 'p'; break;
						case KNIGHT: piece_char = (color == WHITE) ? 'N' : 'n'; break;
						case BISHOP: piece_char = (color == WHITE) ? 'B' : 'b'; break;
						case ROOK: piece_char = (color == WHITE) ? 'R' : 'r'; break;
						case QUEEN: piece_char = (color == WHITE) ? 'Q' : 'q'; break;
						case KING: piece_char = (color == WHITE) ? 'K' : 'k'; break;
						default: piece_char = ' '; break;
					}
				}
			}

			if (piece_char == ' ')
			{
				empty_count++;
			}
			else
			{
				if (empty_count > 0)
				{
					os << empty_count;
					empty_count = 0;
				}
			}

			os << piece_char;
		}

		if (empty_count > 0)
		{
			os << empty_count;
		}

		if (rank > 0)
		{
			os << "/";
		}
	}

	os << " " << (board.active_color == WHITE ? "w" : "b");

	std::stringstream castling_availability;
	if (board.white_kingside_castle) castling_availability << "K";
	if (board.white_queenside_castle) castling_availability << "Q";
	if (board.black_kingside_castle) castling_availability << "k";
	if (board.black_queenside_castle) castling_availability << "q";

	if (castling_availability.str().empty())
	{
		os << " -";
	}
	else
	{
		os << " " << castling_availability.str();
	}

	if (board.en_passant_target_string.empty())
	{
		os << " -";
	}
	else
	{
		os << " " << board.en_passant_target_string;
	}

	os << " " << board.halfmove_clock << " " << board.fullmove_number;

}