#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <variant>
#include <functional>
#include <optional>
#include <vector>
#include <stack>

#include "SemanticError.hpp"
#include "SemanticTable.hpp"
#include "Token.hpp"


namespace wpl {

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

struct Name_Provider {
    std::string name_id;

    bool function_call {};
    bool subscript_access {};
};

struct Value_Provider {
    Type type;
};

struct Expression_Node {
    Type type;

    std::variant<Name_Provider, Value_Provider, std::monostate> value {};
};

class Semantic
{
public:
    std::size_t scope_count {};
    Name_Table name_table {};

    std::stack<std::size_t> scopes {};
    std::stack<Type> types {};
    std::stack<Name> names {};
    std::stack<Name_Provider> name_providers {};
    std::stack<Value_Provider> value_providers {};
    std::stack<Expression_Node> expression_nodes {};

    auto execute_action(int action, Token const* token) -> void;

    auto get_name(std::function<bool(Name const&)> const& predicate) -> std::optional<Name*>;
    auto get_name(std::size_t scope, std::string const& id) -> std::optional<Name*>;
    auto get_name(std::string const& id) -> std::optional<Name*>;

    auto get_name_table() const -> Name_Table;

private:
    auto do_scope_action(int suffix, Token const* token) -> void;
    auto do_type_action(int suffix, Token const* token) -> void;
    auto do_declare_action(int suffix, Token const* token) -> void;
    auto do_function_action(int suffix, Token const* token) -> void;
    auto do_name_provider_action(int suffix, Token const* token) -> void;
    auto do_value_provider_action(int suffix, Token const* token) -> void;
    auto do_value_access_action(int suffix, Token const* token) -> void;
    auto do_assignment_action(int suffix, Token const* token) -> void;
    auto do_expression_handling_action(int suffix, Token const* token) -> void;

    auto try_get_name(std::string const& id) -> std::optional<Name*>;
    auto try_put_name(Name const& name) -> void;

    auto verify_scope_lifetime(std::size_t scope) -> void;
    auto sanitize_type_compatibility(Name const* name, Type const& type) -> void;
    auto sanitize_type_compatibility(Name const& name, Type const& type) -> void;
    auto sanitize_check_declared(std::string const& id) -> void;

    auto infer_any_type(Type const& decl_type, Expression_Node const& node) -> Type;
};

} //namespace wpl

#endif
