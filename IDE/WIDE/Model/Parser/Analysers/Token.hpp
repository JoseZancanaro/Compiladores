#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Constants.hpp"

#include <string>

namespace wpl {

class Token
{
public:
    Token(Token_Id id, const std::string &lexeme, int position)
      : id(id), lexeme(lexeme), position(position) { }

    auto get_id() const -> Token_Id { return id; }
    auto get_lexeme() const -> std::string const& { return lexeme; }
    auto get_position() const -> int { return position; }

private:
    Token_Id id;
    std::string lexeme;
    int position;
};

} //namespace wpl

#endif
