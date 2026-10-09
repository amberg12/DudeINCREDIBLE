#include "dude_incredible/version.hpp"

#include <print>

int main() {
  std::println("Hello, {}", dude_incredible::version::to_string());
}
