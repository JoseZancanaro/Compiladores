#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <functional>
#include <optional>
#include <vector>
#include <stack>

#include "Token.hpp"
#include "SemanticError.hpp"

namespace wpl {

enum class Type_Name {
    UNKNOWN,
    VOID,
    INTEGER,
    FLOAT,
    DOUBLE,
    BOOL,
    CHAR,
    STRING,
    ANY
};

struct Type {
    std::string name;

    // Type Flags
    bool array {};
    bool pointer {};
    bool ref {};
    bool constant {};
};

struct Name {
    std::size_t scope;
    std::string id;
    Type type;
    Type inferred;

    // Compiler Flags
    bool initialized {};
    bool read {};

    // Function Flags
    bool param {};
    bool function {};
};

using Name_Table = std::vector<Name>;

auto get_type_name(Type_Name const& type) -> std::string;
auto get_type(std::string const& type) -> Type_Name;

class Semantic
{
public:
    std::size_t scope_count {};
    Name_Table name_table {};

    std::stack<std::size_t> scopes {};
    std::stack<Type> types {};
    std::stack<Name> names {};

    auto execute_action(int action, Token const* token) -> void;

    auto do_scope_action(int suffix, Token const* token) -> void;
    auto do_type_action(int suffix, Token const* token) -> void;
    auto do_declare_action(int suffix, Token const* token) -> void;
    auto do_function_action(int suffix, Token const* token) -> void;
    auto do_access_control_action(int suffix, Token const* token) -> void;

    auto get_name(std::function<bool(Name const&)> const& predicate) -> std::optional<Name*>;
    auto get_name(std::size_t scope, std::string const& id) -> std::optional<Name*>;
    auto get_name(std::string const& id) -> std::optional<Name*>;

    auto try_put_name(Name const& name) -> void;

    auto get_name_table() const -> Name_Table;

private:
    auto verify_scope_lifetime(std::size_t scope) -> void;
};

} //namespace wpl

#endif
