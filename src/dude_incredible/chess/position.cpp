#include "dude_incredible/chess/position.hpp"

#include "dude_incredible/utility/tokenizer.hpp"

namespace dude_incredible::chess {
  auto Position::from_fen(std::string_view fen) -> Position {
    Position result;

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

    return result;
  }
}  // namespace dude_incredible::chess
