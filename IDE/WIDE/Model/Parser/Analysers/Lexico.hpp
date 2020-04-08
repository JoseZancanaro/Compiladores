#ifndef LEXICAL_HPP
#define LEXICAL_HPP

#include "Token.hpp"
#include "LexicalError.hpp"

#include <string>
#include <iostream>

namespace wpl {

class Lexico
{
public:
    Lexico(std::istream &input) { setInput(input); }
    Lexico() : position(0), input("") { }

    void setInput(std::istream &input);
    void setPosition(unsigned pos) { position = pos; }
    Token *nextToken();

private:
    unsigned position;
    std::string input;

    int nextState(unsigned char c, int state) const;
    TokenId tokenForState(int state) const;
    TokenId lookupToken(TokenId base, const std::string &key);

    bool hasInput() const { return position < input.size(); }
    char nextChar() { return hasInput() ? input[position++] : (char) -1; }
};

} //namespace wpl

#endif
