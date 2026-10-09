#include "dude_incredible/uci/uci.hpp"

#include <iostream>
#include <print>

auto main(int argc, char* argv[]) -> int {
  dude_incredible::uci::UciHandler uci;

  if (argc == 1) {
    std::string line;
    while (std::getline(std::cin, line)) {
      if (line == "quit") {
        break;
      }

      uci.parse_command(line);
    }
  } else {
    ++argv;
    --argc;

    for (dude_incredible::i32 i = 0; i < argc; ++i) {
      uci.parse_command(argv[i]);
    }
  }
}
