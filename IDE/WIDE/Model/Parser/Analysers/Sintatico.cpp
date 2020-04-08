#include "Sintatico.hpp"

#include "Symbols.hpp"

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

bool Sintatico::step()
{
    if (currentToken == 0) //Fim de Sentensa
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
            return false;
        }
        case ACCEPT:
            return true;

        case ERROR:
            throw SyntaticError(PARSER_ERROR[state], currentToken->getPosition());
    }
    return false;
}

std::stack<Composite<std::string>> Sintatico::getTree() const
{
    return this->tree;
}

} //namespace wpl

