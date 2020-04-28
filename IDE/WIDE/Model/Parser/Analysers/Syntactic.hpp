#ifndef SYNTACTIC_HPP
#define SYNTACTIC_HPP

#include "../../Composite.hpp"
#include "Constants.hpp"
#include "Token.hpp"
#include "Lexical.hpp"
#include "Semantic.hpp"
#include "SyntaticError.hpp"

#include <stack>

namespace wpl {

class Syntactic
{
public:
    Syntactic() : current_token(0), previous_token(0) { }

    auto create_detailed_error(int state, Token* token) const -> Syntatic_Error;

    auto parse(Lexical *scanner, Semantic *semantic_analyser) -> void;

    auto get_tree() const -> std::stack<Composite<std::string>>;

    ~Syntactic()
    {
        if (previous_token != 0 && previous_token != current_token) delete previous_token;
        if (current_token != 0)  delete current_token;
    }

private:
    std::stack<Composite<std::string>> tree {};
    std::stack<int> stack;
    Token* current_token;
    Token* previous_token;
    Lexical* scanner;
    Semantic* semantic_analyser;

    auto step() -> bool;
};

} //namespace wpl

#endif
