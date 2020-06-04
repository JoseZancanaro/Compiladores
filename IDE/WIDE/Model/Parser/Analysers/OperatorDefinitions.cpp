#include "OperatorDefinitions.hpp"

namespace wpl {

auto is_relational(std::string const& op) -> bool {
    return op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=";
}

auto is_unary_arithmetic(std::string const& op) -> bool {
    return op == "++" || op == "--";
}

}
