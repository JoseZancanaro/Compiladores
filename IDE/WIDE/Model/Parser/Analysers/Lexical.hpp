#ifndef LEXICAL_HPP
#define LEXICAL_HPP

#include "Token.hpp"
#include "LexicalError.hpp"

#include <string>

namespace wpl {

class Lexical
{
public:
    Lexical(const char *input = "") { set_input(input); }

    auto set_input(const char *input) -> void;
    auto set_position(unsigned pos) -> void { position = pos; }
    auto next_token() -> Token*;

private:
    unsigned position;
    std::string input;

    auto next_state(unsigned char c, int state) const -> int;
    auto token_for_state(int state) const -> Token_Id;
    auto lookup_token(Token_Id base, const std::string &key) -> Token_Id;

    auto has_input() const -> bool { return position < input.size(); }
    auto next_char() -> char { return has_input() ? input[position++] : static_cast<char>(-1); }
};

} //namespace wpl

#endif
