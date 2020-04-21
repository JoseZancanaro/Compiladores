#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <vector>
#include <stack>

#include "Token.hpp"
#include "SemanticError.hpp"

namespace wpl {

enum Type {
    VOID,
    INTEGER,
    FLOAT,
    DOUBLE,
    BOOL,
    CHAR,
    STRING,
    ANY
};

struct Name {
    std::string id;
    std::string scope;
    std::string type;
    std::string inferred;

    // Compiler Flags
    bool initialized {};
    bool read {};

    // Type Flags
    bool const param {};
    bool const array {};
    bool const pointer {};
    bool const ref {};
    bool const function {};
    bool const constant {};
};

using NameTable = std::vector<Name>;

auto getTypeName(Type const& type) -> std::string;
auto getType(std::string const& type) -> Type;

class Semantico
{
public:
    NameTable name_table {};

    std::stack<std::string> scopes {};
    std::stack<std::string> types {};
    std::stack<std::string> names {};

    void executeAction(int action, Token const* token);

    void doScopeAction(int action, const Token *token);
    void doTypeAction(int action, Token const* token);
    void doDeclareAction(int action, const Token *token);

    void try_put_name(Name const& name);
};

} //namespace wpl

#endif
