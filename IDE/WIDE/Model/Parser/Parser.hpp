#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include <string>
#include <vector>

#include "Analysers/Lexico.hpp"
#include "Analysers/Sintatico.hpp"
#include "Analysers/Semantico.hpp"
#include "../Composite.hpp"

namespace wpl::language {

class Parser
{
    wpl::Lexico lex;
    wpl::Sintatico syntactic;
    wpl::Semantico semantic;

    struct ParserContext {
        std::vector<wpl::AnalysisError> errors;
        bool success;
        std::optional<Composite<std::string>> tree;
    };

public:
    Parser();
    Parser(std::string const&);

    auto parse() -> ParserContext;
    auto parse(std::string const&) -> ParserContext;
};

}

#endif // PARSER_HPP
