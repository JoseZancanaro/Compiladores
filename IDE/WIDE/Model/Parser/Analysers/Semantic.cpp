#include "Semantic.hpp"
#include "Constants.hpp"

#include <iostream>
#include <tuple>

namespace wpl {

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
        case 4: {
            this->do_name_provider_action(suffix, token);
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
        case 11: {
            this->do_value_access_action(suffix, token);
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

            this->try_put_name(name); //@TODO Check type

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
                              { get_type_description(Type_Name::UNKNOWN) },
                              { get_type_description(Type_Name::UNKNOWN) }
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
    enum class Name_Provider_Suffix {
        SET_NAME_VAR_ID = 0,
        SET_NAME_FUNCTION_ID = 3
    };

    switch (Name_Provider_Suffix(suffix)) {
        case Name_Provider_Suffix::SET_NAME_VAR_ID:
        case Name_Provider_Suffix::SET_NAME_FUNCTION_ID: {
            this->name_providers.push({ token->get_lexeme() });
            break;
        }
    }
}

auto Semantic::do_value_access_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    enum class Value_Access_Suffix {
        NAME_ACCESS = 0,
        LITERAL_ACCESS = 1
    };

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

                // @TODO Put node in value stack
            }

            break;
        }
        case Value_Access_Suffix::LITERAL_ACCESS: {
            // @TODO Literal access
        }
    }
}

auto Semantic::do_assignment_action(int suffix, [[maybe_unused]] Token const* token) -> void {
    enum class Assignment_Suffix {
        ASSIGN = 0
    };

    switch (Assignment_Suffix(suffix)) {
        case Assignment_Suffix::ASSIGN: {
            auto provider = this->name_providers.top();

            if (auto name = this->try_get_name(provider.name_id); name.has_value()) {
                name.value()->initialized = true;

                // @TODO Verify type compatibility
            }

            break;
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
            std::cerr << "Variable declared and its value was never read: " << name.id << std::endl; // @Todo Logger class
        }
    }
}

auto Semantic::sanitize_check_declared([[maybe_unused]] std::string const& id) -> void {} // @TODO Refactor

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

} //namespace wpl

