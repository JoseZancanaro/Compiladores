#include "Semantic.hpp"
#include "Constants.hpp"

#include <iostream>
#include <tuple>

namespace wpl {

auto get_type_name(Type_Name const& type) -> std::string  {

    switch (type) {
    case Type_Name::UNKNOWN: return "Unknown";
    case Type_Name::VOID:    return "Void";
    case Type_Name::INTEGER: return "Integer";
    case Type_Name::FLOAT:   return "Float";
    case Type_Name::DOUBLE:  return "Double";
    case Type_Name::BOOL:    return "Bool";
    case Type_Name::CHAR:    return "Char";
    case Type_Name::STRING:  return "String";
    case Type_Name::ANY:     return "Any";
    }
}

auto get_type(std::string const& name) -> Type_Name {
    if (name == "Unknown") {
        return Type_Name::UNKNOWN;
    } else if (name == "Void") {
        return Type_Name::VOID;
    } else if (name == "Integer") {
        return Type_Name::INTEGER;
    } else if (name == "Float") {
        return Type_Name::FLOAT;
    } else if (name == "Double") {
        return Type_Name::DOUBLE;
    } else if (name == "Bool") {
        return Type_Name::BOOL;
    } else if (name == "Char") {
        return Type_Name::CHAR;
    } else if (name == "String") {
        return Type_Name::STRING;
    } else if (name == "Any") {
        return Type_Name::ANY;
    } else {
        return Type_Name::UNKNOWN;
    }
}

auto decode_action(int action) -> std::pair<int, int> {
    return { action / 100, action % 100 };
}

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
        case 11: {
            this->do_access_control_action(suffix, token);
            break;
        }
    }
}

auto Semantic::do_scope_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    enum class Scope_Suffix {
        PUSH_GLOBAL = 0,
        POP_GLOBAL = 1,
        PUSH_QUALIFIED = 2,
        POP_QUALIFIED = 3

    };

    auto to_string = [](Type const& type) {
        std::string vector = type.array ? "[]" : "";
        std::string constant = type.constant ? " const" : "";
        std::string ref = type.ref ? "&" : "";
        std::string pointer = type.pointer ? "*" : "";

        return type.name + vector + constant + ref + pointer;
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
                          << " " << to_string(n.type) << " " << n.read << std::endl;
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
    enum class Type_Suffix {
        PUSH_TYPE_NAME = 0,
        SET_VEC_MODIFIER = 1,
        ACK_VEC_SIZE_MODIFIER = 2,
        SET_VEC_SIZE_MODIFIER = 3,
        SET_CONST_MODIFIER = 4,
        SET_REF_MODIFIER = 5,
        SET_POINTER_MODIFIER = 6,
    };

    switch (Type_Suffix(suffix)) {
        case Type_Suffix::PUSH_TYPE_NAME: {
            this->types.push({ token->get_lexeme() });
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
    enum class Declare_Suffix {
        PUSH_NAME_ID = 0,
        PUSH_INITIALIZED = 1,
        PUSH_UNINITIALIZED = 2,
        POP_TYPE = 3
    };

    switch (Declare_Suffix(suffix)) {
        case Declare_Suffix::PUSH_NAME_ID: {
            this->names.push({ this->scopes.top(), token->get_lexeme(), this->types.top(), this->types.top() });

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

auto Semantic::do_function_action(int suffix, Token const* token) -> void {
    enum class Function_Suffix {
        NAME_DISCOVER = 0,
        NAME_FUNC_PUSH = 1,
        NAME_PARAM_PUSH = 2
    };

    switch (Function_Suffix(suffix)) {
        case Function_Suffix::NAME_DISCOVER: {
            this->names.push({ this->scopes.top(), token->get_lexeme(),
                              { get_type_name(Type_Name::UNKNOWN) },
                              { get_type_name(Type_Name::UNKNOWN) }
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

auto Semantic::do_access_control_action(int suffix, Token const* token) -> void {
    enum class Access_Control_Suffix {
        NAME_VALUE = 0,
        FUNCTION_CALL = 1,
        VECTOR_CHILD = 2
    };

    switch (Access_Control_Suffix(suffix)) {
        case Access_Control_Suffix::NAME_VALUE:
        case Access_Control_Suffix::FUNCTION_CALL:
        case Access_Control_Suffix::VECTOR_CHILD: {
            auto id = token->get_lexeme();

            if (auto name = this->get_name(id); name.has_value()) {
                std::cout << "Setting " << name.value()->id << " as read" << std::endl;
                name.value()->read = true;

                std::cout << name.value()->read << std::endl;
            }
            else {
                std::cerr << "Use of undeclared name: " << id << std::endl;
            }

            break;
        }
    }
}

auto Semantic::verify_scope_lifetime(std::size_t scope) -> void {
    std::vector<std::tuple<std::size_t, std::string, bool>> exceptions = {
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
            std::cerr << "Variable declared and it's value was never read: " << name.id << std::endl; // @Todo Logger class
        }
    }
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

auto Semantic::try_put_name(const Name& name) -> void {
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

} //namespace wpl

