#pragma once

namespace dude_incredible::chess {
  struct CastlingRights {
    std::optional<i8> king_side = std::nullopt;
    std::optional<i8> queen_side = std::nullopt;

    [[nodiscard]] static constexpr auto empty() -> CastlingRights {
      return CastlingRights {std::nullopt, std::nullopt};
    }
  };
}  // namespace dude_incredible::chess
