#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include "Token.hpp"
#include "SemanticError.hpp"

namespace wpl {

class Semantico
{
public:
    void executeAction(int action, const Token *token);
};

} //namespace wpl

#endif
