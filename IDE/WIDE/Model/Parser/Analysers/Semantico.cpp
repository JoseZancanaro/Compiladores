#include "Semantico.hpp"
#include "Constants.hpp"

#include <iostream>

namespace wpl {

void Semantico::executeAction(int action, const Token *token)
{
    std::cout << "Ação: " << action << ", Token: "  << token->getId() 
              << ", Lexema: " << token->getLexeme() << std::endl;
}

} //namespace wpl

