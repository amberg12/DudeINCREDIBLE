#pragma once
#include <charconv>
#include <optional>
#include <string_view>
#include <type_traits>

namespace dude_incredible::numeric {
  template<class T>
    requires std::is_arithmetic_v<T>
  auto parse_number(std::string_view sv) -> std::optional<T> {
    if (T value {}; std::from_chars(sv.data(), sv.data() + sv.size(), value).ec == std::errc {}) {
      return value;
    }

    return std::nullopt;
  }
}  // namespace dude_incredible::numeric
