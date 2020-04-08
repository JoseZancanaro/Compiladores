#include "Parser.hpp"

#include <sstream>

namespace wpl::language {

Parser::Parser()
    : lex{}, syntactic{}, semantic{}
{}

Parser::Parser(std::string const& input)
    : lex{}, syntactic{}, semantic{}
{
    std::stringstream ss;
    ss << input;
    lex.setInput(ss);
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
    std::stringstream ss;
    ss << input;
    this->lex.setInput(ss);
    return this->parse();
}

}
