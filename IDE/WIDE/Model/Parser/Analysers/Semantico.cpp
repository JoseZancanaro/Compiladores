#include "Semantico.hpp"
#include "Constants.hpp"

#include <iostream>

namespace wpl {

auto getTypeName(Type const& type) -> std::string  {
    switch (type) {
    case VOID:
        return "Void";
    case INTEGER:
        return "Integer";
    case FLOAT:
        return "Float";
    case DOUBLE:
        return "Double";
    case BOOL:
        return "Bool";
    case CHAR:
        return "Char";
    case STRING:
        return "String";
    case ANY:
        return "Any";
    default:
        return "Unknown";
    }
}

auto decode_action(int action) -> std::pair<int, int> {
    return { action / 100, action % 100 };
}

auto Semantico::execute_action(int action, const Token *token) -> void {
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
        case 11: {
            this->do_access_control_action(suffix, token);
            break;
        }
    }
}

auto Semantico::do_scope_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    switch (suffix) {
        case 0: {
            this->scopes.push(this->scope_count++);
            break;
        }
        case 1: {
            this->scopes.pop();

            for (auto const& n : this->name_table) {
                std::cout << n.id << " " << n.scope << " " << n.type << " " << n.inferred << std::endl;
            }

            break;
        }
        case 2: {
            this->scopes.push(this->scope_count++);
            break;
        }
        case 3: {
            this->scopes.pop();
            break;
        }
    }
}

auto Semantico::do_type_action(int suffix, Token const* token) -> void {
    switch (suffix) {
        case 0: {
            this->types.push(token->getLexeme());
            break;
        }
    }
}

auto Semantico::do_declare_action(int suffix, Token const* token) -> void {
    switch (suffix) {
        case 0: {
            this->try_put_name({ this->scopes.top(), token->getLexeme(), this->types.top(), this->types.top() });
            break;
        }
        case 1: {



            break;
        }
        case 2: {
            this->types.pop();
            break;
        }
    }
}

auto Semantico::do_function_action(int suffix, Token const* token) -> void {
    enum FunctionSuffix {
        NAME_DISCOVER = 0,
        NAME_FUNC_PUSH = 1,
        NAME_PARAM_PUSH = 2
    };

    switch (FunctionSuffix(suffix)) {
        case NAME_DISCOVER: {
            this->names.push({ token->getLexeme(), this->scopes.top() });

            break;
        }
        case NAME_FUNC_PUSH: {
            auto const& [ function_name, parent_scope ] = this->names.top();
            this->names.pop();

            auto function_type = this->types.top();
            this->types.pop();

            Name name { parent_scope, function_name, function_type, function_type };
            name.function = true;

            this->try_put_name(name); // @TODO sanitizer

            break;
        }
        case NAME_PARAM_PUSH: {
            auto param_name = token->getLexeme();
            auto param_type = this->types.top();
            this->types.pop();

            Name name { this->scopes.top(), param_name, param_type, param_type };
            name.param = true;

            this->try_put_name(name); // @TODO sanitizer

            break;
        }
    }
}

auto Semantico::do_access_control_action(int suffix, Token const* token) -> void {
    enum AccessControlSuffix {
        NAME_VALUE = 0,
        FUNCTION_CALL = 1,
        VECTOR_CHILD = 2
    };

    switch (AccessControlSuffix(suffix)) {
        case NAME_VALUE:
        case FUNCTION_CALL:
        case VECTOR_CHILD: {
            auto id = token->getLexeme();

            if (!this->get_name(id).has_value()) {
                std::cerr << "Use of undeclared name: " << id << std::endl;
            }

            break;
        }
    }
}

auto Semantico::get_name(std::function<bool(Name const&)> const& predicate) -> std::optional<Name> {
    for (auto & name : this->name_table) {
        if (predicate(name)) {
            return std::make_optional(name);
        }
    }

    return std::nullopt;
}

auto Semantico::get_name(std::size_t scope, std::string const& id) -> std::optional<Name> {
    return this->get_name([scope, &id](Name const& name) {
        return name.scope == scope && name.id == id;
    });
}

auto Semantico::get_name(std::string const& id) -> std::optional<Name> {
    auto scopes_copy = this->scopes;

    while (!scopes_copy.empty()) {
        if (auto name = this->get_name(scopes_copy.top(), id); name.has_value()) {
            return name;
        }
        scopes_copy.pop();
    }

    return std::nullopt;
}

void Semantico::try_put_name(const Name& name)
{
    this->name_table.push_back(name);
}

} //namespace wpl

