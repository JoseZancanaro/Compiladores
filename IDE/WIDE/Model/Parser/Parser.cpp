#include "Parser.hpp"

#include <iostream>

namespace wpl::language {

Parser::Parser()
    : lex{}, syntactic{}, semantic{}
{}

Parser::Parser(std::string const& input)
    : lex{}, syntactic{}, semantic{}
{
    lex.set_input(input.c_str());
}

auto Parser::parse() -> Parser_Context {
    try {
        syntactic.parse(&lex, &semantic);
        return Parser_Context{{}, true, syntactic.get_tree().top(), semantic.get_name_table() };
    } catch (wpl::Analysis_Error e) {
        return Parser_Context{{e}, false, {}, semantic.get_name_table() };
    }
}

auto Parser::parse(std::string const& input) -> Parser_Context {
    this->lex.set_input(input.c_str());
    return this->parse();
}

}
