#pragma once
#include <optional>
#include <string_view>

namespace dude_incredible::chess {
  struct Square {
    inline static constexpr usize count = 64;

    u8 raw = 0x80;

    constexpr Square() = default;

    /* implicit */ constexpr Square(u8 raw)
        : raw(raw) {
    }

    constexpr Square(i8 file, i8 rank)
        : raw(rank * 8 + file) {
    }

    [[nodiscard]] static constexpr auto safe_construct_square(i8 file, i8 rank) -> std::optional<Square> {
      const auto valid_coord = [](i8 n) -> bool {
        return 0 <= n && n < 8;
      };

      if (!valid_coord(file) && !valid_coord(rank)) {
        return std::nullopt;
      }

      return Square {file, rank};
    }

    [[nodiscard]] static constexpr auto parse(std::string_view sv) -> std::optional<Square> {
      const auto valid_coord = [](i8 n) -> bool {
        return 0 <= n && n < 8;
      };

      if (sv.size() != 2) {
        return std::nullopt;
      }

      const i8 file = static_cast<i8>(sv[0] - 'a');

      if (!valid_coord(file)) {
        return std::nullopt;
      }

      const i8 rank = static_cast<i8>(sv[1] - '1');

      if (!valid_coord(rank)) {
        return std::nullopt;
      }

      return Square {file, rank};
    }

    static constexpr auto none() -> Square {
      return 0x80;
    }

    [[nodiscard]] constexpr auto is_some() const -> bool {
      return (raw & 0x80) == 0;
    }

    [[nodiscard]] constexpr auto is_none() const -> bool {
      return !is_some();
    }

    [[nodiscard]] constexpr auto to_index() const -> usize {
      return raw;
    }
  };
}  // namespace dude_incredible::chess
