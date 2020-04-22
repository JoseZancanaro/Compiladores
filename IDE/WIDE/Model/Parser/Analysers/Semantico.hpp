#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <functional>
#include <optional>
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
    std::size_t scope;
    std::string id;
    std::string type;
    std::string inferred;

    // Compiler Flags
    bool initialized {};
    bool read {};

    // Type Flags
    bool param {};
    bool array {};
    bool pointer {};
    bool ref {};
    bool function {};
    bool constant {};
};

using NameTable = std::vector<Name>;

auto getTypeName(Type const& type) -> std::string;
auto getType(std::string const& type) -> Type;

class Semantico
{
public:
    std::size_t scope_count {};
    NameTable name_table {};

    std::stack<std::size_t> scopes {};
    std::stack<std::string> types {};
    std::stack<std::pair<std::string, std::size_t>> names {};

    auto execute_action(int action, Token const* token) -> void;

    auto do_scope_action(int suffix, Token const* token) -> void;
    auto do_type_action(int suffix, Token const* token) -> void;
    auto do_declare_action(int suffix, Token const* token) -> void;
    auto do_function_action(int suffix, Token const* token) -> void;
    auto do_access_control_action(int suffix, Token const* token) -> void;

    auto get_name(std::function<bool(Name const&)> const& predicate) -> std::optional<Name>;
    auto get_name(std::size_t scope, std::string const& id) -> std::optional<Name>;
    auto get_name(std::string const& id) -> std::optional<Name>;

    auto try_put_name(Name const& name) -> void;
};

} //namespace wpl

#endif
