#pragma once

#include "dude_incredible/numeric/numeric_types.hpp"

namespace dude_incredible::chess {
  struct Color {
    inline static constexpr usize count = 2;

    enum Underlying : bool {
      w = false,
      b = true,
    };

    Underlying raw = w;

    constexpr Color() = default;

    /* implicit */ constexpr Color(Underlying raw)
        : raw(raw) {
    }

    friend constexpr auto operator==(const Color& lhs, const Color& rhs) -> bool = default;
  };

  template<class T>
  struct ColorArray {
    T inner[2];

    constexpr auto operator[](Color perspective) const -> const T& {
      return inner[perspective.raw];
    }

    constexpr auto operator[](Color perspective) -> T& {
      return inner[perspective.raw];
    }
  };

  struct Piece {
    inline static constexpr usize count = 7;

    enum Underlying : u8 {
      none = 0b000,
      p = 0b001,
      n = 0b010,
      b = 0b011,
      r = 0b100,
      q = 0b101,
      k = 0b110,
    };

    Underlying raw = none;

    /* implicit */ constexpr Piece(Underlying raw)
        : raw(raw) {
    }

    [[nodiscard]] constexpr auto is_some() const -> bool {
      return raw != none;
    }

    [[nodiscard]] constexpr auto is_none() const -> bool {
      return !is_some();
    }
  };
}  // namespace dude_incredible::chess
