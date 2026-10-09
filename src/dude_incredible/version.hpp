#pragma once

#include <format>
#include <string_view>

namespace dude_incredible::version {
  extern const std::string_view version;
  extern const std::string_view git_commit_hash;

  inline auto to_string() -> std::string {
    return std::format("{}-{}", version, git_commit_hash);
  }
}