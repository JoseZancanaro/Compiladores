#include "Syntactic.hpp"

#include "Symbols.hpp"

#include <iostream>

namespace wpl {

void Syntactic::parse(Lexical *scanner, Semantic *semanticAnalyser)
{
    this->scanner = scanner;
    this->semantic_analyser = semanticAnalyser;

    //Limpa a pilha
    while (! stack.empty())
        stack.pop();

    stack.push(0);

    if (previous_token != 0 && previous_token != current_token)
        delete previous_token;
    previous_token = 0;

    if (current_token != 0)
        delete current_token;
    current_token = scanner->next_token();

    while ( ! step() )
        ;
}

// Custom error report :)
Syntatic_Error Syntactic::create_detailed_error(int state, Token* token) const
{
    auto error = std::string("Error at state ") + std::to_string(state);

    auto pair = std::string(" (") + std::to_string(token->get_position())
                    + ", " + token->get_lexeme() + "): ";

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

    return Syntatic_Error(error + pair + buffer, token->get_position());
}

bool Syntactic::step()
{
    if (current_token == 0) //Fim de Sentença
    {
        int pos = 0;
        if (previous_token != 0)
            pos = previous_token->get_position() + previous_token->get_lexeme().size();

        current_token = new Token(DOLLAR, "$", pos);
    }

    int token = current_token->get_id();
    int state = stack.top();

    const int* cmd = PARSER_TABLE[state][token-1];

    switch (cmd[0])
    {
        case SHIFT:
        {
            stack.push(cmd[1]);
            if (previous_token != 0)
                delete previous_token;

            this->tree.push(Composite(std::string(symbols[current_token->get_id()]) + " : " + current_token->get_lexeme()));

            previous_token = current_token;
            current_token = scanner->next_token();
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
            semantic_analyser->execute_action(cmd[1], previous_token);

            this->tree.push(std::string("#") + std::to_string(cmd[1]));

            return false;
        }
        case ACCEPT:
            return true;

        case ERROR:
            throw create_detailed_error(state, current_token);
    }
    return false;
}

std::stack<Composite<std::string>> Syntactic::get_tree() const
{
    return this->tree;
}

} //namespace wpl

