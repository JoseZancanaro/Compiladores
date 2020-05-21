#ifndef ACTIONDEFINITIONS_HPP
#define ACTIONDEFINITIONS_HPP

#include <utility>

constexpr auto action_size = 100;
constexpr auto action_unary_expression_size = 90;

constexpr auto decode_action(int action) -> std::pair<int, int> {
    return { action / action_size, action % action_size };
}

constexpr auto is_unary_expression_suffix(int suffix) -> bool {
    return suffix / action_unary_expression_size >= 1;
}

enum class Scope_Suffix {
    PUSH_GLOBAL = 0,
    POP_GLOBAL = 1,
    PUSH_QUALIFIED = 2,
    POP_QUALIFIED = 3
};

enum class Type_Suffix {
    PUSH_TYPE_NAME = 0,
    SET_VEC_MODIFIER = 1,
    ACK_VEC_SIZE_MODIFIER = 2,
    SET_VEC_SIZE_MODIFIER = 3,
    SET_CONST_MODIFIER = 4,
    SET_REF_MODIFIER = 5,
    SET_POINTER_MODIFIER = 6,
};

enum class Declare_Suffix {
    PUSH_NAME_ID = 0,
    PUSH_INITIALIZED = 1,
    PUSH_UNINITIALIZED = 2,
    POP_TYPE = 3
};

enum class Function_Suffix {
    NAME_DISCOVER = 0,
    NAME_FUNC_PUSH = 1,
    NAME_PARAM_PUSH = 2
};

enum class Name_Provider_Suffix {
    SET_NAME_VAR_ID = 0,
    SET_SUBSCRIPT_ACCESS = 1,
    SET_SUBSCRIPT_INDEX = 2,
    SET_NAME_FUNCTION_ID = 3,
    SET_CALL_ARG = 4,
    SET_CALL_END = 5
};

enum class Value_Provider_Suffix {
    PUSH_INT = 0,
    PUSH_DOUBLE = 1,
    PUSH_BOOL = 2,
    PUSH_CHAR = 3,
    PUSH_STRING = 4
};

enum class Value_Access_Suffix {
    NAME_ACCESS = 0,
    LITERAL_ACCESS = 1
};

enum class Assignment_Suffix {
    ASSIGN = 0
};

enum class Unary_Expression_Handling_Suffix {
    ARITHMETIC_ADD = 90,
    ARITHMETIC_SUB = 91,

    LOGICAL_NOT = 92,

    BITWISE_COMP = 93,

    ATTRIBUTION_PREFIX_INC = 94,
    ATTRIBUTION_PREFIX_DEC = 95,
    ATTRIBUTION_POSTFIX_INC = 96,
    ATTRIBUTION_POSTFIX_DEC = 97
};

enum class Binary_Expression_Handling_Suffix {
    LOGICAL_OR = 0,
    LOGICAL_AND = 1,

    BITWISE_OR = 10,
    BITWISE_XOR = 11,
    BITWISE_AND = 12,
    BITWISE_SR = 13,
    BITWISE_SL = 14,

    RELATIONAL_EQ = 20,
    RELATIONAL_NEQ = 21,
    RELATIONAL_GT = 22,
    RELATIONAL_LT = 23,
    RELATIONAL_GTE = 24,
    RELATIONAL_LTE = 25,

    ARITHMETIC_ADD = 30,
    ARITHMETIC_SUB = 31,
    ARITHMETIC_MULT = 32,
    ARITHMETIC_DIV = 33,
    ARITHMETIC_REM = 34,
    ARITHMETIC_EXP = 35,
};

enum class Vector_Constructor_Suffix {
    BEGIN_FILLED_DECL = 0,
    END_FILLED_DECL = 1,
    PUSH_EMPTY = 2,
    PUSH_VALUE = 3
};

#endif // ACTIONDEFINITIONS_HPP
