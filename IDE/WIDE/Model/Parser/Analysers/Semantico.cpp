#include "Semantico.hpp"
#include "Constants.hpp"

#include <iostream>

namespace wpl {

auto get_type_name(Type const& type) -> std::string  {

    switch (type) {
    case Type::UNKNOWN: return "Unknown";
    case Type::VOID:    return "Void";
    case Type::INTEGER: return "Integer";
    case Type::FLOAT:   return "Float";
    case Type::DOUBLE:  return "Double";
    case Type::BOOL:    return "Bool";
    case Type::CHAR:    return "Char";
    case Type::STRING:  return "String";
    case Type::ANY:     return "Any";
    }
}

auto get_type(std::string const& name) -> Type {
    if (name == "Unknown") {
        return Type::UNKNOWN;
    } else if (name == "Void") {
        return Type::VOID;
    } else if (name == "Integer") {
        return Type::INTEGER;
    } else if (name == "Float") {
        return Type::FLOAT;
    } else if (name == "Double") {
        return Type::DOUBLE;
    } else if (name == "Bool") {
        return Type::BOOL;
    } else if (name == "Char") {
        return Type::CHAR;
    } else if (name == "String") {
        return Type::STRING;
    } else if (name == "Any") {
        return Type::ANY;
    } else {
        return Type::UNKNOWN;
    }
}

auto decode_action(int action) -> std::pair<int, int> {
    return { action / 100, action % 100 };
}

auto Semantico::execute_action(int action, Token const* token) -> void {
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
        case 11: {
            this->do_access_control_action(suffix, token);
            break;
        }
    }
}

auto Semantico::do_scope_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    enum class Scope_Suffix {
        PUSH_GLOBAL = 0,
        POP_GLOBAL = 1,
        PUSH_QUALIFIED = 2,
        POP_QUALIFIED = 3

    };

    switch (Scope_Suffix(suffix)) {
        case Scope_Suffix::PUSH_GLOBAL: {
            this->scopes.push(this->scope_count++);
            break;
        }
    case Scope_Suffix::POP_GLOBAL: {
            this->scopes.pop();

            for (auto const& n : this->name_table) {
                std::cout << n.id << " " << n.scope << " " << n.type << " " << n.inferred << std::endl;
            }

            break;
        }
    case Scope_Suffix::PUSH_QUALIFIED: {
            this->scopes.push(this->scope_count++);
            break;
        }
        case Scope_Suffix::POP_QUALIFIED: {
            this->scopes.pop();
            break;
        }
    }
}

auto Semantico::do_type_action(int suffix, Token const* token) -> void {
    enum class Type_Suffix {
        PUSH_TYPENAME = 0,

    };

    switch (Type_Suffix(suffix)) {
        case Type_Suffix::PUSH_TYPENAME: {
            this->types.push(token->getLexeme());
            break;
        }
    }
}

auto Semantico::do_declare_action(int suffix, Token const* token) -> void {
    enum class Declare_Suffix {
        PUSH_NAME_ID = 0,
        PUSH_INITIALIZED = 1,
        PUSH_UNINITIALIZED = 2,
        POP_TYPE = 3
    };

    switch (Declare_Suffix(suffix)) {
        case Declare_Suffix::PUSH_NAME_ID: {
            this->names.push({ this->scopes.top(), token->getLexeme(), this->types.top(), this->types.top() });

            break;
        }
        case Declare_Suffix::PUSH_INITIALIZED: {
            auto name = this->names.top(); this->names.pop();
            name.initialized = true;

            //@TODO check type

            this->try_put_name(name);

            break;
        }
        case Declare_Suffix::PUSH_UNINITIALIZED: {
            auto name = this->names.top(); this->names.pop();
            this->try_put_name(name);

            break;
        }
        case Declare_Suffix::POP_TYPE: {
            this->types.pop();
            break;
        }
    }
}

auto Semantico::do_function_action(int suffix, Token const* token) -> void {
    enum class Function_Suffix {
        NAME_DISCOVER = 0,
        NAME_FUNC_PUSH = 1,
        NAME_PARAM_PUSH = 2
    };

    switch (Function_Suffix(suffix)) {
        case Function_Suffix::NAME_DISCOVER: {
            this->names.push({ this->scopes.top(), token->getLexeme(), get_type_name(Type::UNKNOWN), get_type_name(Type::UNKNOWN) });
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
    enum class Access_Control_Suffix {
        NAME_VALUE = 0,
        FUNCTION_CALL = 1,
        VECTOR_CHILD = 2
    };

    switch (Access_Control_Suffix(suffix)) {
        case Access_Control_Suffix::NAME_VALUE:
        case Access_Control_Suffix::FUNCTION_CALL:
        case Access_Control_Suffix::VECTOR_CHILD: {
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

