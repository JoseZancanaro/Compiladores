#include "Sintatico.hpp"

#include "Symbols.hpp"

#include <iostream>

namespace wpl {

void Sintatico::parse(Lexico *scanner, Semantico *semanticAnalyser)
{
    this->scanner = scanner;
    this->semanticAnalyser = semanticAnalyser;

    //Limpa a pilha
    while (! stack.empty())
        stack.pop();

    stack.push(0);

    if (previousToken != 0 && previousToken != currentToken)
        delete previousToken;
    previousToken = 0;

    if (currentToken != 0)
        delete currentToken;
    currentToken = scanner->nextToken();

    while ( ! step() )
        ;
}

// Custom error report :)
SyntaticError Sintatico::createDetailedError(int state, Token* token) const
{
    auto error = std::string("Error at state ") + std::to_string(state);

    auto pair = std::string(" (") + std::to_string(token->getPosition())
                    + ", " + token->getLexeme() + "): ";

    auto productions = PARSER_TABLE[state];
    auto const qty = sizeof(symbols) / sizeof(symbols[0]);

    std::vector<std::string> expected;

    for (std::size_t i = 1; i < qty; ++i) {
        if (auto const production = productions[i];
            production[0] != ERROR && std::string(symbols[i + 1]).find("<") == std::string::npos) {
            expected.push_back(symbols[i + 1]);
        }
    }

    std::string buffer("Expected ");

    if (expected.size() > 1) {
        for (std::size_t i = 0; i < expected.size() - 1; ++i) {
            buffer += expected.at(i) + ", ";
        }
        buffer += "ou " + expected.at(expected.size() - 1) + ".";
    } else if (expected.size() == 1) {
        buffer += expected.at(0) + ".";
    }

    return SyntaticError(error + pair + buffer, token->getPosition());
}

bool Sintatico::step()
{
    if (currentToken == 0) //Fim de Sentença
    {
        int pos = 0;
        if (previousToken != 0)
            pos = previousToken->getPosition() + previousToken->getLexeme().size();

        currentToken = new Token(DOLLAR, "$", pos);
    }

    int token = currentToken->getId();
    int state = stack.top();

    const int* cmd = PARSER_TABLE[state][token-1];

    switch (cmd[0])
    {
        case SHIFT:
        {
            stack.push(cmd[1]);
            if (previousToken != 0)
                delete previousToken;

            this->tree.push(Composite(std::string(symbols[currentToken->getId()]) + " : " + currentToken->getLexeme()));

            previousToken = currentToken;
            currentToken = scanner->nextToken();
            return false;
        }
        case REDUCE:
        {
            const int* prod = PRODUCTIONS[cmd[1]];

            std::stack<Composite<std::string>> temp;

            for (int i=0; i<prod[1]; i++) {
                stack.pop();
                temp.push(tree.top());
                tree.pop();
            }

            int oldState = stack.top();

            Composite<std::string> root {std::string(symbols[prod[0]])};

            stack.push(PARSER_TABLE[oldState][prod[0]-1][1]);

            while (!temp.empty()) {
                root.children.push_back(temp.top());
                temp.pop();
            }

            this->tree.push(root);

            return false;
        }
        case ACTION:
        {
            int action = FIRST_SEMANTIC_ACTION + cmd[1] - 1;
            stack.push(PARSER_TABLE[state][action][1]);
            semanticAnalyser->executeAction(cmd[1], previousToken);

            this->tree.push(std::string("#") + std::to_string(cmd[1]));

            return false;
        }
        case ACCEPT:
            return true;

        case ERROR:
            throw createDetailedError(state, currentToken);
    }
    return false;
}

std::stack<Composite<std::string>> Sintatico::getTree() const
{
    return this->tree;
}

} //namespace wpl

