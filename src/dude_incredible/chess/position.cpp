#include "dude_incredible/chess/position.hpp"

#include "dude_incredible/utility/tokenizer.hpp"

namespace dude_incredible::chess {
  auto Position::from_fen(std::string_view fen) -> Position {
    //Position result;

    auto toks = utility::Tokenizer(std::string {fen});

    throw PositionParseError::bad_coordinates();
  }
}  // namespace dude_incredible::chess
