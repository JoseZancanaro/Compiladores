#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include <string>
#include <vector>

#include "Analysers/Lexical.hpp"
#include "Analysers/Syntactic.hpp"
#include "Analysers/Semantic.hpp"
#include "../Composite.hpp"

namespace wpl::language {

class Parser
{
    wpl::Lexical lex;
    wpl::Syntactic syntactic;
    wpl::Semantic semantic;

    struct Parser_Context {
        std::vector<Issue> issues;
        bool success;
        std::optional<Composite<std::string>> tree;
        Name_Table name_table {};
    };

public:
    Parser(std::unique_ptr<Logger_Base> logger = std::make_unique<Null_Logger>());
    Parser(std::string const&, std::unique_ptr<Logger_Base> logger = std::make_unique<Null_Logger>());

    auto parse() -> Parser_Context;
    auto parse(std::string const&) -> Parser_Context;
};

}

#endif // PARSER_HPP
