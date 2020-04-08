#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Constants.hpp"

#include <string>

namespace wpl {

class Token
{
public:
    Token(TokenId id, const std::string &lexeme, int position)
      : id(id), lexeme(lexeme), position(position) { }

    TokenId getId() const { return id; }
    const std::string &getLexeme() const { return lexeme; }
    int getPosition() const { return position; }

private:
    TokenId id;
    std::string lexeme;
    int position;
};

} //namespace wpl

#endif
