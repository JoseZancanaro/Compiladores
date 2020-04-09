#ifndef LEXICO_HPP
#define LEXICO_HPP

#include "Token.hpp"
#include "LexicalError.hpp"

#include <string>

namespace wpl {

class Lexico
{
public:
    Lexico(const char *input = "") { setInput(input); }

    void setInput(const char *input);
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
