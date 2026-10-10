#pragma once

#include "dude_incredible/chess/board.hpp"
#include "dude_incredible/chess/castling_rights.hpp"

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

    [[nodiscard]] static constexpr auto malformed_perspective() -> PositionParseError {
      return PositionParseError {"Malformed Perspective"};
    }

    [[nodiscard]] static constexpr auto malformed_frc_castling() -> PositionParseError {
      return PositionParseError {"Malformed FRC Castling"};
    }

    [[nodiscard]] static constexpr auto malformed_castling() -> PositionParseError {
      return PositionParseError {"Malformed Castling"};
    }

    [[nodiscard]] static constexpr auto malformed_en_passant() -> PositionParseError {
      return PositionParseError {"Malformed EnPassant Square"};
    }

    [[nodiscard]] static constexpr auto malformed_half_move() -> PositionParseError {
      return PositionParseError {"Malformed Half Move"};
    }

    [[nodiscard]] static constexpr auto malformed_full_move() -> PositionParseError {
      return PositionParseError {"Malformed Full Move"};
    }

  private:
    explicit PositionParseError(const std::string& msg)
        : std::runtime_error(msg) {
    }
  };

  struct Position {
    [[nodiscard]] static auto from_fen(std::string_view fen, bool is_frc = false) -> Position;

    [[nodiscard]] auto to_fen() const -> std::string;

  private:
    Position() = default;

    MailBox mail_box_;
    Color perspective_;
    ColorArray<CastlingRights> castling_rights_ = {CastlingRights::empty(), CastlingRights::empty()};
    Square en_passant_;
    u8 half_move_ = 0;
    u32 full_move_ = 1;

    bool is_frc_ = false;
  };
}  // namespace dude_incredible::chess
