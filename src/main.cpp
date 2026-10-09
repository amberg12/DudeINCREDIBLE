#include <print>

#include "dude_incredible/version.hpp"

int main() {
  std::println("Hello, {}", dude_incredible::version::to_string());;
}