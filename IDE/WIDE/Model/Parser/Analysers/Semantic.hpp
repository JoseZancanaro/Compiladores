#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <sstream>
#include <variant>
#include <functional>
#include <optional>
#include <memory>
#include <vector>
#include <stack>

#include "Model/Parser/Asm/BipDefinitions.hpp"
#include "LoggerBase.hpp"
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
    bool reserved {};

    // Function Flags
    std::size_t param_pos {};
    bool param {};
    bool function {};
};

using Name_Table = std::vector<Name>;

struct Name_Provider {
    std::string name_id;

    bool function_call {};
    bool subscript_access {};
    size_t subscript_position {};
};

struct Call_Context {
    Name* name = nullptr;
    std::size_t total_args {};
    std::size_t arg_count {};
};

struct Value_Provider {
    Type type;
};

struct Expression_Node {
    Type type;

    std::variant<Name_Provider, Value_Provider, std::monostate> value {};
};

struct Issue {
    enum class Issue_Type {
        WARNING = 0,
        ERROR = 1
    };

    Issue_Type type;
    std::string message;

    auto to_string() const -> std::string {
        if (type == Issue_Type::WARNING) {
            return "Warning: " + message;
        } else {
            return "Error: " + message;
        }
    }
};

class Semantic
{
public:
    Semantic(std::unique_ptr<Logger_Base> && p_logger = std::make_unique<Null_Logger>());

    Name_Table name_table {};
    std::vector<Issue> issues {};

    std::stack<std::size_t> scopes {};
    std::stack<Type> types {};
    std::stack<Name> names {};
    std::stack<Name_Provider> name_providers {};
    std::stack<Value_Provider> value_providers {};
    std::stack<Expression_Node> expression_nodes {};
    std::stack<Call_Context> call_contexts {};

    // Context variables
    std::size_t scope_count {};
    std::size_t parameter_count {};

    auto execute_action(int action, Token const* token) -> void;

    auto get_name(std::function<bool(Name const&)> const& predicate) -> std::optional<Name*>;
    auto get_name(std::size_t scope, std::string const& id) -> std::optional<Name*>;
    auto get_name(std::string const& id) -> std::optional<Name*>;

    auto get_name_table() const -> Name_Table;
    auto get_issues() const -> std::vector<Issue>;
    auto get_program() const -> bip_asm::BIP_Program;

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

    auto fetch_function_arg_count(Name const& name) -> std::size_t;

    auto verify_scope_lifetime(std::size_t scope) -> void;
    auto sanitize_type(Type const& type, bool param = false, bool function = false) -> void;
    auto sanitize_type_compatibility(Name const* name, Type const& type) -> void;
    auto sanitize_type_compatibility(Name const& name, Type const& type) -> void;
    auto sanitize_check_declared(std::string const& id) -> void;

    auto infer_any_type(Type const& decl_type, Expression_Node const& node) -> Type;

    auto issue_warning(std::string && message) noexcept -> void;
    auto issue_error(std::string && message) -> void;

    struct GenerationContext {
        std::stack<bool> binary_second_operand {};
        std::stack<std::string> operators {};
    };

    // @TODO separate asm generation
    auto bip_asm_data(Name const& name) -> void;
    auto bip_asm_text(std::string const& op, std::string const& operand) -> void;

    GenerationContext gc {};
    bip_asm::BIP_Program compiled {};
    std::unique_ptr<Logger_Base> logger;
};

} //namespace wpl

namespace wpl::detail {

    template <typename ... T>
    auto to_string(T ... t) -> std::string {
        std::stringstream ss;

        ((ss << t), ...);

        return ss.str();
    }

} //namespace wpl::detail

#endif
