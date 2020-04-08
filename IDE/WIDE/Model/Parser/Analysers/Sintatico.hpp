#ifndef SYNTACTIC_HPP
#define SYNTACTIC_HPP

#include "../../Composite.hpp"
#include "Constants.hpp"
#include "Token.hpp"
#include "Lexico.hpp"
#include "Semantico.hpp"
#include "SyntaticError.hpp"

#include <stack>

namespace wpl {

class Sintatico
{
public:
    Sintatico() : currentToken(0), previousToken(0) { }

    ~Sintatico()
    {
        if (previousToken != 0 && previousToken != currentToken) delete previousToken;
        if (currentToken != 0)  delete currentToken;
    }

    void parse(Lexico *scanner, Semantico *semanticAnalyser);

    std::stack<Composite<std::string>> getTree() const;

private:
    std::stack<Composite<std::string>> tree {};
    std::stack<int> stack;
    Token *currentToken;
    Token *previousToken;
    Lexico *scanner;
    Semantico *semanticAnalyser;

    bool step();
};

} //namespace wpl

#endif
