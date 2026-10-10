#pragma once

namespace dude_incredible::chess {
  struct Square {
    inline static constexpr usize count = 64;

    u8 raw = 0x80;

    constexpr Square() = default;

    /* implicit */ constexpr Square(u8 raw)
        : raw(raw) {
    }

    constexpr Square(i8 rank, i8 file)
        : raw(rank * 8 + file) {
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
