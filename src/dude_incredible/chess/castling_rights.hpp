#pragma once

#include "dude_incredible/chess/piece.hpp"
#include "dude_incredible/numeric/numeric_types.hpp"

#include <optional>
#include <string>

namespace dude_incredible::chess {
  struct Position;

  struct CastlingRights {
    std::optional<i8> king_side = std::nullopt;
    std::optional<i8> queen_side = std::nullopt;

    [[nodiscard]] static constexpr auto empty() -> CastlingRights {
      return CastlingRights {std::nullopt, std::nullopt};
    }

    [[nodiscard]] auto to_string(Color perspective, const Position& ctx) const -> std::string;
  };
}  // namespace dude_incredible::chess
