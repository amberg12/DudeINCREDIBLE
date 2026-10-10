#pragma once

#include "dude_incredible/chess/piece.hpp"
#include "dude_incredible/chess/square.hpp"

#include <array>

namespace dude_incredible::chess {
  struct Place {
    inline static constexpr u8 color_mask = 0b1000;
    inline static constexpr u8 piece_mask = 0b0111;

    u8 raw = 0;

    constexpr Place() = default;

    constexpr Place(Color perspective, Piece piece)
        : raw(get_color_mask(perspective) | get_piece_mask(piece)) {
    }

    [[nodiscard]] static constexpr auto parse(char c) -> std::optional<Place> {
      switch (c) {
      case 'P':
        return Place {Color::w, Piece::p};
      case 'N':
        return Place {Color::w, Piece::n};
      case 'B':
        return Place {Color::w, Piece::b};
      case 'R':
        return Place {Color::w, Piece::r};
      case 'Q':
        return Place {Color::w, Piece::q};
      case 'K':
        return Place {Color::w, Piece::k};
      case 'p':
        return Place {Color::b, Piece::p};
      case 'n':
        return Place {Color::b, Piece::n};
      case 'b':
        return Place {Color::b, Piece::b};
      case 'r':
        return Place {Color::b, Piece::r};
      case 'q':
        return Place {Color::b, Piece::q};
      case 'k':
        return Place {Color::b, Piece::k};
      default:
        return std::nullopt;
      }
    }

    [[nodiscard]] constexpr auto color() const -> Color {
      return (raw & color_mask) == 0 ? Color::w : Color::b;
    }

    [[nodiscard]] constexpr auto piece() const -> Piece {
      return Piece {static_cast<Piece::Underlying>(raw & piece_mask)};
    }

    [[nodiscard]] constexpr auto is_some() const -> bool {
      return raw != 0;
    }

    [[nodiscard]] constexpr auto is_none() const -> bool {
      return !is_some();
    }

  private:
    [[nodiscard]] static constexpr auto get_color_mask(Color perspective) -> u8 {
      return perspective == Color::w ? 0 : color_mask;
    }

    [[nodiscard]] static constexpr auto get_piece_mask(Piece piece) -> u8 {
      return piece.raw;
    }
  };

  struct MailBox {
    std::array<Place, Square::count> mailbox;

    auto operator[](Square square) -> Place& {
      return mailbox[square.to_index()];
    }

    auto operator[](Square square) const -> const Place& {
      return mailbox[square.to_index()];
    }
  };
}  // namespace dude_incredible::chess
