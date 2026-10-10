#include "dude_incredible/chess/castling_rights.hpp"

namespace dude_incredible::chess {
  auto CastlingRights::to_string(Color perspective, const Position& ctx) const -> std::string {
    (void)ctx;

    std::string result;

    if (king_side.has_value()) {
      result += perspective == Color::w ? 'K' : 'k';
    }

    if (queen_side.has_value()) {
      result += perspective == Color::w ? 'Q' : 'q';
    }

    return result.empty() ? "-" : result;
  }
}  // namespace dude_incredible::chess
