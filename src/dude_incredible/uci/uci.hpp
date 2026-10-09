#pragma once
#include "dude_incredible/utility/tokenizer.hpp"

#include <format>
#include <print>
#include <string_view>

namespace dude_incredible::uci {
  struct UciHandler {
    auto parse_command(std::string_view) -> void;

  private:
    auto handle_uci(utility::Tokenizer&) -> void;

    template<class... Args>
    auto uci_error(std::string_view cmd, std::format_string<Args...> fmt, Args&&... args) -> void {
      std::println("info string `{}`: {}", cmd, std::format(fmt, args...));
    }

    auto uci_bad_cmd(std::string_view cmd) -> void {
      uci_error(cmd, "Unknown Command");
    }
  };
}  // namespace dude_incredible::uci
