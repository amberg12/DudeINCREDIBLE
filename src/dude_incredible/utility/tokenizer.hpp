#pragma once

#include "dude_incredible/numeric/numeric_types.hpp"

#include <string>
#include <string_view>
#include <utility>

namespace dude_incredible::utility {
  struct Tokenizer {
    explicit Tokenizer(std::string text)
        : buffer_(std::move(text))
        , str_(std::string_view {buffer_}) {
    }

    // Delete other constructors due to relying on backing std::string-std::string_view dynamics
    Tokenizer(const Tokenizer& other) = delete;
    Tokenizer(Tokenizer&& other) = delete;
    Tokenizer& operator=(const Tokenizer& other) = delete;
    Tokenizer& operator=(Tokenizer&& other) = delete;

    auto next() -> std::string_view {
      const std::string_view result = [this] {
        const usize index = str_.find_first_of(whitespace_);
        const std::string_view r = str_.substr(0, index);
        str_.remove_prefix(index != std::string_view::npos ? index : str_.size());
        return r;
      }();

      const usize ws_to_trim = str_.find_first_not_of(whitespace_);

      if (ws_to_trim != std::string_view::npos) {
        str_.remove_prefix(ws_to_trim);
      }

      return result;
    }

  private:
    std::string buffer_;
    std::string_view str_;

    inline static constexpr std::string_view whitespace_ = " \t\n";
  };
}  // namespace dude_incredible::utility
