#include "Semantic.hpp"
#include "Constants.hpp"
#include "ActionDefinitions.hpp"

#include <iostream>
#include <tuple>

namespace wpl {

auto Semantic::execute_action(int action, Token const* token) -> void {
    //@TODO enum class

    auto [ prefix, suffix ] = decode_action(action);

    switch (prefix) {
        case 0: {
            this->do_scope_action(suffix, token);
            break;
        }
        case 1: {
            this->do_type_action(suffix, token);
            break;
        }
        case 2: {
            this->do_declare_action(suffix, token);
            break;
        }
        case 3: {
            this->do_function_action(suffix, token);
            break;
        }
        case 4: {
            this->do_name_provider_action(suffix, token);
            break;
        }
        case 7: {
            this->do_value_provider_action(suffix, token);
            break;
        }
        case 5: {
            this->do_value_access_action(suffix, token);
            break;
        }
        case 6: {
            this->do_assignment_action(suffix, token);
            break;
        }
        case 8: {
            this->do_expression_handling_action(suffix, token);
            break;
        }
        default: {
            std::cout << "Uncaught action with type "
                      << "Prefix" << prefix
                      << "Suffix" << suffix << std::endl;
        }
    }
}

auto Semantic::do_scope_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    auto to_string = [](Type const& type) {
        std::string vector = type.array ? "[]" : "";
        std::string constant = type.constant ? " const" : "";
        std::string ref = type.ref ? "&" : "";
        std::string pointer = type.pointer ? "*" : "";

        return get_type_description(type.name) + vector + constant + ref + pointer;
    };

    switch (Scope_Suffix(suffix)) {
        case Scope_Suffix::PUSH_GLOBAL: {
            this->scopes.push(this->scope_count++);
            break;
        }
        case Scope_Suffix::POP_GLOBAL: {
            this->verify_scope_lifetime(this->scopes.top());
            this->scopes.pop();

            for (auto const& n : this->name_table) {
                std::cout << n.id << " " << n.scope << " " << to_string(n.type)
                          << " " << to_string(n.inferred) << " " << n.read << std::endl;
            }

            break;
        }
        case Scope_Suffix::PUSH_QUALIFIED: {
                this->scopes.push(this->scope_count++);
                break;
            }
        case Scope_Suffix::POP_QUALIFIED: {
            this->verify_scope_lifetime(this->scopes.top());
            this->scopes.pop();
            break;
        }
    }
}

auto Semantic::do_type_action(int suffix, Token const* token) -> void {
    switch (Type_Suffix(suffix)) {
        case Type_Suffix::PUSH_TYPE_NAME: {
            this->types.push({ get_type_name(token->get_lexeme()) });
            break;
        }
        case Type_Suffix::SET_VEC_MODIFIER:
        case Type_Suffix::ACK_VEC_SIZE_MODIFIER:
        case Type_Suffix::SET_VEC_SIZE_MODIFIER: {
            this->types.top().array = true;
            break;
        }
        case Type_Suffix::SET_CONST_MODIFIER: {
            this->types.top().constant = true;
            break;
        }
        case Type_Suffix::SET_REF_MODIFIER: {
            this->types.top().ref = true;
            break;
        }
        case Type_Suffix::SET_POINTER_MODIFIER: {
            this->types.top().pointer = true;
            break;
        }
    }
}

auto Semantic::do_declare_action(int suffix, Token const* token) -> void {
    switch (Declare_Suffix(suffix)) {
        case Declare_Suffix::PUSH_NAME_ID: {
            this->names.push({ this->scopes.top(), token->get_lexeme(), this->types.top(), this->types.top() });

            //@TODO Check type

            break;
        }
        case Declare_Suffix::PUSH_INITIALIZED: {
            auto name = this->names.top(); this->names.pop();
            name.initialized = true;

            auto expression_node = this->expression_nodes.top();
            this->expression_nodes.pop();

            if (name.type.name == Type_Name::ANY) {
                name.inferred = this->infer_any_type(name.type, expression_node);
            }

            this->sanitize_type_compatibility(name, expression_node.type);

            this->try_put_name(name);

            break;
        }
        case Declare_Suffix::PUSH_UNINITIALIZED: {
            auto name = this->names.top(); this->names.pop();

            if (name.type.name == Type_Name::ANY) {
                std::cerr << "Declaration of name " << name.id
                          << " with deduced type Any requires an initializer" << std::endl; // @TODO Logger Class
            }

            this->try_put_name(name);

            break;
        }
        case Declare_Suffix::POP_TYPE: {
            this->types.pop();
            break;
        }
    }
}

auto Semantic::do_function_action(int suffix, Token const* token) -> void {
    switch (Function_Suffix(suffix)) {
        case Function_Suffix::NAME_DISCOVER: {
            this->names.push({ this->scopes.top(), token->get_lexeme(),
                              { Type_Name::UNKNOWN },
                              { Type_Name::UNKNOWN }
                            });
            break;
        }
        case Function_Suffix::NAME_FUNC_PUSH: {
            auto function_name = this->names.top();
            this->names.pop();

            auto function_type = this->types.top();
            this->types.pop();

            function_name.type = function_type;
            function_name.inferred = function_type;
            function_name.function = true;

            this->try_put_name(function_name); // @TODO sanitizer

            break;
        }
        case Function_Suffix::NAME_PARAM_PUSH: {
            auto param_name = token->get_lexeme();
            auto param_type = this->types.top();
            this->types.pop();

            Name name { this->scopes.top(), param_name, param_type, param_type };
            name.param = true;

            this->try_put_name(name); // @TODO sanitizer

            break;
        }
    }
}

auto Semantic::do_name_provider_action(int suffix, Token const* token) -> void {
    switch (Name_Provider_Suffix(suffix)) {
        case Name_Provider_Suffix::SET_NAME_VAR_ID:
        case Name_Provider_Suffix::SET_NAME_FUNCTION_ID: {
            this->name_providers.push({ token->get_lexeme() });
            break;
        }
    }
}

auto Semantic::do_value_provider_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    switch (Value_Provider_Suffix(suffix)) {
        case Value_Provider_Suffix::PUSH_INT: {
            this->value_providers.push({ Type_Name::INTEGER });
            break;
        }
        case Value_Provider_Suffix::PUSH_DOUBLE: {
            this->value_providers.push({ Type_Name::DOUBLE });
            break;
        }
        case Value_Provider_Suffix::PUSH_BOOL: {
            this->value_providers.push({ Type_Name::BOOL });
            break;
        }
        case Value_Provider_Suffix::PUSH_CHAR: {
            this->value_providers.push({ Type_Name::CHAR });
            break;
        }
        case Value_Provider_Suffix::PUSH_STRING: {
            this->value_providers.push({ Type_Name::STRING });
            break;
        }
    }
}

auto Semantic::do_value_access_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    switch (Value_Access_Suffix(suffix)) {
        case Value_Access_Suffix::NAME_ACCESS: {
            auto provider = this->name_providers.top();
            this->name_providers.pop();

            if (auto name_opt = this->try_get_name(provider.name_id); name_opt.has_value()) {
                auto name = name_opt.value();
                name->read = true;

                if (!name->initialized) {
                    std::cerr << "Name " << name->id << " is unitialized when used." << std::endl; // @TODO Logger class
                }

                this->expression_nodes.push({ name->inferred });
            }

            break;
        }
        case Value_Access_Suffix::LITERAL_ACCESS: {
            auto provider = this->value_providers.top();
            this->value_providers.pop();

            this->expression_nodes.push({ provider.type });
        }
    }
}

auto Semantic::do_assignment_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    switch (Assignment_Suffix(suffix)) {
        case Assignment_Suffix::ASSIGN: {
            auto provider = this->name_providers.top();
            this->name_providers.pop();

            auto expression_node = this->expression_nodes.top();
            this->expression_nodes.pop();

            if (auto name_opt = this->try_get_name(provider.name_id); name_opt.has_value()) {
                auto name = name_opt.value();
                name->initialized = true;

                this->sanitize_type_compatibility(name, expression_node.type);
            }

            break;
        }
    }
}

auto Semantic::do_expression_handling_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    auto push_result_type = [&](Expression_Node && node) {
        if (node.type.name != Type_Name::INVALID) {
            this->expression_nodes.push(std::move(node));
        } else {
            this->expression_nodes.push(std::move(node));
            std::cerr << "Invalid result type" << std::endl; // @TODO Move to class scope, Logger class
        }
    };

    if (is_unary_expression_suffix(suffix)) {
        auto node = this->expression_nodes.top();
        this->expression_nodes.pop();

        switch (Unary_Expression_Handling_Suffix(suffix)) {
            case Unary_Expression_Handling_Suffix::ARITHMETIC_ADD:
            case Unary_Expression_Handling_Suffix::ARITHMETIC_SUB: {
                if (type_traits::is_numeric(node.type)) {
                    push_result_type({ node.type });
                } else {
                    push_result_type({{ Type_Name::INVALID }});
                    std::cerr << "Unary arithmetic operator on non numeric type." << std::endl; // @TODO Logger class
                }
                break;
            }
            case Unary_Expression_Handling_Suffix::LOGICAL_NOT: {
                if (type_traits::is_truthy_type(node.type)) {
                    push_result_type({{ Type_Name::BOOL }});
                } else {
                    push_result_type({{ Type_Name::INVALID }});
                    std::cerr << "Unary negate operator on non truthy type." << std::endl; // @TODO Logger class
                }
                break;
            }
            case Unary_Expression_Handling_Suffix::BITWISE_COMP: {
                if (type_traits::is_integral(node.type)) {
                    push_result_type({ node.type });
                } else {
                    push_result_type({{ Type_Name::INVALID }});
                    std::cerr << "Unary complement operator on non integral type." << std::endl; // @TODO Logger class
                }
                break;
            }
            case Unary_Expression_Handling_Suffix::ATTRIBUTION_PREFIX_INC:
            case Unary_Expression_Handling_Suffix::ATTRIBUTION_PREFIX_DEC:
            case Unary_Expression_Handling_Suffix::ATTRIBUTION_POSTFIX_INC:
            case Unary_Expression_Handling_Suffix::ATTRIBUTION_POSTFIX_DEC: {
                if (type_traits::is_numeric(node.type)) {
                    push_result_type({ node.type });
                } else {
                    push_result_type({{ Type_Name::INVALID }});
                    std::cerr << "Unary arithmetic operator on non numeric type." << std::endl; // @TODO Logger class
                }
                break;
            }
        }
    } else {
        auto left = this->expression_nodes.top();
        this->expression_nodes.pop();

        auto right = this->expression_nodes.top();
        this->expression_nodes.pop();

        switch (Binary_Expression_Handling_Suffix(suffix)) {
            case Binary_Expression_Handling_Suffix::LOGICAL_OR:
            case Binary_Expression_Handling_Suffix::LOGICAL_AND: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::LOGICAL) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::BITWISE_OR:
            case Binary_Expression_Handling_Suffix::BITWISE_XOR:
            case Binary_Expression_Handling_Suffix::BITWISE_AND:
            case Binary_Expression_Handling_Suffix::BITWISE_SR:
            case Binary_Expression_Handling_Suffix::BITWISE_SL: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::BITWISE) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::RELATIONAL_EQ:
            case Binary_Expression_Handling_Suffix::RELATIONAL_NEQ:
            case Binary_Expression_Handling_Suffix::RELATIONAL_GT:
            case Binary_Expression_Handling_Suffix::RELATIONAL_LT:
            case Binary_Expression_Handling_Suffix::RELATIONAL_GTE:
            case Binary_Expression_Handling_Suffix::RELATIONAL_LTE: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::RELATIONAL) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::ARITHMETIC_ADD: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::ADD) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::ARITHMETIC_SUB: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::SUB) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::ARITHMETIC_MULT: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::MULT) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::ARITHMETIC_DIV: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::DIV) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::ARITHMETIC_REM: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::REM) }
                });
                break;
            }
            case Binary_Expression_Handling_Suffix::ARITHMETIC_EXP: {
                push_result_type({
                    { Semantic_Table::get_result_type(left.type.name, right.type.name, Operator::EXP) }
                });
                break;
            }
            default: {
                std::cerr << "Uncaught " << suffix << std::endl;
            }
        }
    }
}

auto Semantic::verify_scope_lifetime(std::size_t scope) -> void {
    static std::vector<std::tuple<std::size_t, std::string, bool>> exceptions = {
        {0, "main", true}
    };

    auto is_exception = [&](Name const& name) -> bool {
        return std::any_of(std::begin(exceptions), std::end(exceptions), [&name](auto const& tuple) -> bool {
            auto [ scope, id, function ] = tuple;

            return name.scope == scope && name.id == id && name.function == function;
        });
    };

    for (auto const& name : this->name_table) {
        if (name.scope == scope && !is_exception(name) && !name.read) {
            std::cerr << "Name declared and its value was never read: " << name.id << std::endl; // @Todo Logger Class
        }
    }
}

auto Semantic::sanitize_check_declared([[maybe_unused]] std::string const& id) -> void {} // @TODO Refactor

auto Semantic::sanitize_type_compatibility(Name const* name, Type const& type) -> void {
    if (auto support = Semantic_Table::get_type_compatibility(name->inferred.name, type.name);
        support == Type_Compatibility::NONE) {
        std::cerr << "Can't assign " << get_type_description(type.name)
                  << " into " << get_type_description(name->inferred.name) << std::endl; // @TODO Logger Class
    } else if (support == Type_Compatibility::NARROWING) {
        std::cerr << "Narrowing " << get_type_description(type.name)
                  << " into " << get_type_description(name->inferred.name) << std::endl;
    }
}

auto Semantic::sanitize_type_compatibility(Name const& name, Type const& type) -> void {
    this->sanitize_type_compatibility(&name, type);
}

auto Semantic::get_name(std::function<bool(Name const&)> const& predicate) -> std::optional<Name*> {
    for (auto & name : this->name_table) {
        if (predicate(name)) {
            return std::make_optional(&name);
        }
    }

    return std::nullopt;
}

auto Semantic::get_name(std::size_t scope, std::string const& id) -> std::optional<Name*> {
    return this->get_name([scope, &id](Name const& name) {
        return name.scope == scope && name.id == id;
    });
}

auto Semantic::get_name(std::string const& id) -> std::optional<Name*> {
    auto scopes_copy = this->scopes;

    while (!scopes_copy.empty()) {
        if (auto name = this->get_name(scopes_copy.top(), id); name.has_value()) {
            return name;
        }
        scopes_copy.pop();
    }

    return std::nullopt;
}

auto Semantic::try_get_name(std::string const& id) -> std::optional<Name*> {
    if (auto name = this->get_name(id); name.has_value()) {
        return name;
    } else {
        std::cerr << "Use of undeclared name: " << id << std::endl; // @TODO Logger class
        return std::nullopt;
    }
}

auto Semantic::try_put_name(Name const& name) -> void {
    if (this->get_name(name.scope, name.id).has_value()) {
        std::cerr << "Redefinition of " << name.id << std::endl; // @TODO Logger class
    }
    else {
        this->name_table.push_back(name);
    }
}

auto Semantic::get_name_table() const -> Name_Table {
    return this->name_table;
}

auto Semantic::infer_any_type(Type const& type, Expression_Node const& node) -> Type {
    return { node.type.name, node.type.array, type.pointer, type.ref, type.constant };
}

} //namespace wpl

