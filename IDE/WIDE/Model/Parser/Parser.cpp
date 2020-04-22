#include "Parser.hpp"

#include <iostream>

namespace wpl::language {

Parser::Parser()
    : lex{}, syntactic{}, semantic{}
{}

Parser::Parser(std::string const& input)
    : lex{}, syntactic{}, semantic{}
{
    lex.setInput(input.c_str());
}

auto Parser::parse() -> ParserContext {
    try {
        syntactic.parse(&lex, &semantic);
        return ParserContext{{}, true, syntactic.getTree().top() };
    } catch (wpl::AnalysisError e) {
        return ParserContext{{e}, false, {}};
    }
}

auto Parser::parse(std::string const& input) -> ParserContext {
    this->lex.setInput(input.c_str());
    return this->parse();
}

}
