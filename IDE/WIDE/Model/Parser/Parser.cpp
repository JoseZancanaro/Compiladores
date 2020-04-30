#include "Parser.hpp"

#include <iostream>

namespace wpl::language {

Parser::Parser(std::unique_ptr<Logger_Base> logger)
    : lex{}, syntactic{}, semantic{std::move(logger)}
{}

Parser::Parser(std::string const& input, std::unique_ptr<Logger_Base> logger)
    : lex{}, syntactic{}, semantic{std::move(logger)}
{
    lex.set_input(input.c_str());
}

auto Parser::parse() -> Parser_Context {
    try {
        syntactic.parse(&lex, &semantic);
        return Parser_Context{semantic.get_issues(), true, syntactic.get_tree().top(), semantic.get_name_table() };
    } catch (std::exception const& e) {
        return Parser_Context{{{ Issue::Issue_Type::ERROR, e.what() }}, false, {}, semantic.get_name_table() };
    } catch (wpl::Analysis_Error const& e) {
        return Parser_Context{semantic.get_issues(), false, {}, semantic.get_name_table() };
    }
}

auto Parser::parse(std::string const& input) -> Parser_Context {
    this->lex.set_input(input.c_str());
    return this->parse();
}

}
