#include "dude_incredible/chess/position.hpp"

#include "dude_incredible/numeric/numeric_parsing.hpp"
#include "dude_incredible/utility/tokenizer.hpp"

namespace dude_incredible::chess {
  auto Position::from_fen(std::string_view fen, bool is_frc) -> Position {
    Position result;
    result.is_frc_ = is_frc;

    auto toks = utility::Tokenizer(std::string {fen});

    // Parse Place
    const std::string_view fen_place = toks.next();

    if (fen_place.empty()) {
      throw PositionParseError::malformed_fen();
    }

    {
      i8 file = 0;
      i8 rank = 7;

      for (const auto c : fen_place) {
        if (c == '/') {
          --rank;
          file = 0;
        } else if (std::isdigit(c)) {
          file = static_cast<i8>(file + c - '0');
        } else {
          const auto place = Place::parse(c);

          if (!place) {
            throw PositionParseError::malformed_piece(c);
          }

          if (const auto square = Square::safe_construct_square(file, rank)) {
            result.mail_box_[*square] = *place;
            ++file;
          } else {
            throw PositionParseError::bad_coordinates();
          }
        }
      }
    }

    // Parse Color
    const std::string_view fen_color = toks.next();

    if (fen_color.empty()) {
      throw PositionParseError::malformed_fen();
    }

    if (fen_color == "w") {
      result.perspective_ = Color::w;
    } else if (fen_color == "b") {
      result.perspective_ = Color::b;
    } else {
      throw PositionParseError::malformed_perspective();
    }

    // Parse Castling Rights
    const std::string_view fen_castling = toks.next();

    if (fen_castling.empty()) {
      throw PositionParseError::malformed_fen();
    }

    if (is_frc) {
      throw PositionParseError::malformed_frc_castling();
    }

    if (fen_castling != "-") {
      ColorArray new_castling = {CastlingRights::empty(), CastlingRights::empty()};

      for (const auto c : fen_castling) {
        switch (c) {
        case 'K': {
          new_castling[Color::w].king_side = 7;
        } break;
        case 'k': {
          new_castling[Color::b].king_side = 7;
        } break;
        case 'Q': {
          new_castling[Color::w].queen_side = 0;
        } break;
        case 'q': {
          new_castling[Color::b].queen_side = 0;
        } break;
        default:
          throw PositionParseError::malformed_castling();
        }
      }

      result.castling_rights_ = new_castling;
    }

    // Parse En Passant
    const std::string_view fen_en_passant = toks.next();

    if (fen_en_passant.empty()) {
      throw PositionParseError::malformed_fen();
    }

    if (fen_en_passant == "-") {
      result.en_passant_ = Square::none();
    } else {
      if (const auto en_passant = Square::parse(fen_en_passant)) {
        result.en_passant_ = *en_passant;
      } else {
        throw PositionParseError::malformed_en_passant();
      }
    }

    // Parse Half Move
    const std::string_view fen_half_move = toks.next();

    if (!fen_half_move.empty()) {
      if (const auto half_move = numeric::parse_number<u8>(fen_half_move)) {
        result.half_move_ = *half_move;
      } else {
        throw PositionParseError::malformed_half_move();
      }
    }

    // Parse Full Move
    const std::string_view fen_full_move = toks.next();

    if (!fen_full_move.empty()) {
      if (const auto full_move = numeric::parse_number<u32>(fen_full_move); full_move && *full_move > 0) {
        result.full_move_ = *full_move;
      } else {
        throw PositionParseError::malformed_full_move();
      }
    } else {
      throw PositionParseError::malformed_fen();
    }

    return result;
  }

  auto Position::to_fen() const -> std::string {
    std::string result;

    for (i8 rank = 7; rank >= 0; --rank) {
      char accum = '0';

      for (i8 file = 0; file < 8; ++file) {
        const auto square = Square {file, rank};
        const auto place = mail_box_[square];

        if (place.is_some()) {
          if (accum != '0') {
            result += accum;
          }

          result += place.to_char();
          accum = '0';
        } else {
          accum += 1;
        }
      }

      if (accum != '0') {
        result += accum;
      }

      if (rank != 0) {
        result += '/';
      }
    }

    result += ' ';
    result += perspective_ == Color::w ? 'w' : 'b';

    result += ' ';
    result += castling_rights_[Color::w].to_string(Color::w, *this);
    result += castling_rights_[Color::b].to_string(Color::b, *this);

    result += ' ';
    result += en_passant_.to_string();

    result += ' ';
    result += std::to_string(half_move_);

    result += ' ';
    result += std::to_string(full_move_);

    return result;
  }
}  // namespace dude_incredible::chess
