#pragma once

#include "dude_incredible/chess/board.hpp"

#include <format>
#include <stdexcept>
#include <string_view>

namespace dude_incredible::chess {
  class PositionParseError : public std::runtime_error {
  public:
    [[nodiscard]] static constexpr auto bad_coordinates() -> PositionParseError {
      return PositionParseError {"Fen Coordinates Do Not Add Up"};
    }

    [[nodiscard]] static constexpr auto malformed_fen() -> PositionParseError {
      return PositionParseError {"Malformed Fen"};
    }

    [[nodiscard]] static constexpr auto malformed_piece(char c) -> PositionParseError {
      return PositionParseError {std::format("Malformed Piece: {}", c)};
    }

  private:
    explicit PositionParseError(const std::string& msg)
        : std::runtime_error(msg) {
    }
  };

  struct Position {
    [[nodiscard]] static auto from_fen(std::string_view fen) -> Position;

  private:
    Position() = default;

    MailBox mail_box_;
    Color perspective_;
    // Castling castling_rights_;
    Square en_passant_;
    // u8 half_move_ = 0;
    // u32 full_move_ = 1;
  };
}  // namespace dude_incredible::chess
