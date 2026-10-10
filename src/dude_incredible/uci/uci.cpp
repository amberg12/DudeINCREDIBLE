#include "dude_incredible/uci/uci.hpp"

#include "dude_incredible/chess/fens.hpp"
#include "dude_incredible/version.hpp"

namespace dude_incredible::uci {
  auto UciHandler::parse_command(std::string_view in) -> void {
    auto toks = utility::Tokenizer {std::string(in)};
    const std::string_view command = toks.next();

    if (command == "uci") {
      handle_uci(toks);
    } else if (command == "position") {
      handle_position(toks);
    } else if (!command.empty()) {
      uci_bad_cmd(command);
    }
  }

  auto UciHandler::handle_uci(utility::Tokenizer&) -> void {
    std::println("id name DudeINCREDIBLE {}", version::to_string());
    std::println("id author Amber Goulding");
    std::println("uciok");
  }

  auto UciHandler::handle_position(utility::Tokenizer& toks) -> void {
    std::string fen, t;

    t = toks.next();

    if (t == "startpos") {
      fen = fen::startpos;
    } else if (t != "fen") {
      uci_error("position", "Missing fen");
      return;
    } else {
      while ((t = toks.next()).empty() == false || t == "moves") {
        fen += t + " ";
      }
    }

    try {
      position_ = chess::Position::from_fen(fen);
    } catch (const chess::PositionParseError& e) {
      uci_error("position", "Parsing Error: {}", e.what());
      return;
    }
  }

  auto UciHandler::handle_d(utility::Tokenizer&) -> void {
  }
}  // namespace dude_incredible::uci
