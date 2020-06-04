#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace wpl {

enum Token_Id
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_KW_VOID = 2,
    t_KW_INT = 3,
    t_KW_FLOAT = 4,
    t_KW_DOUBLE = 5,
    t_KW_BOOL = 6,
    t_KW_CHAR = 7,
    t_KW_STR = 8,
    t_KW_ANY = 9,
    t_KW_CONST = 10,
    t_KW_VECTOR = 11,
    t_KW_CASE = 12,
    t_KW_OF = 13,
    t_KW_SWITCH = 14,
    t_KW_BREAK = 15,
    t_KW_CHOOSE = 16,
    t_KW_IF = 17,
    t_KW_ELSE = 18,
    t_KW_PIPE = 19,
    t_KW_OTHERWISE = 20,
    t_KW_FOR = 21,
    t_KW_WHILE = 22,
    t_KW_DO = 23,
    t_KW_DEF = 24,
    t_KW_RETURN = 25,
    t_KW_FN_RESERVED = 26,
    t_OP_ATT = 27,
    t_OP_INC = 28,
    t_OP_DEC = 29,
    t_OP_ATT_ADD = 30,
    t_OP_ATT_SUB = 31,
    t_OP_ATT_MULT = 32,
    t_OP_ATT_DIV = 33,
    t_OP_ATT_REM = 34,
    t_OP_ADD = 35,
    t_OP_SUB = 36,
    t_OP_MULT = 37,
    t_OP_DIV = 38,
    t_OP_REM = 39,
    t_OP_EXP = 40,
    t_OP_GT = 41,
    t_OP_LT = 42,
    t_OP_GTE = 43,
    t_OP_LTE = 44,
    t_OP_EQ = 45,
    t_OP_NEQ = 46,
    t_OP_AND = 47,
    t_OP_OR = 48,
    t_OP_NOT = 49,
    t_OP_BW_SR = 50,
    t_OP_BW_SL = 51,
    t_OP_BW_AND = 52,
    t_OP_BW_OR = 53,
    t_OP_BW_COMP = 54,
    t_OP_BW_XOR = 55,
    t_ID_VAR = 56,
    t_ID_FUNC = 57,
    t_VAL_INT = 58,
    t_VAL_INT_BIN = 59,
    t_VAL_INT_HEX = 60,
    t_VAL_REAL = 61,
    t_VAL_CHAR = 62,
    t_VAL_STR = 63,
    t_VAL_BOOL_TRUE = 64,
    t_VAL_BOOL_FALSE = 65,
    t_COMM_SL = 66,
    t_COMM_ML = 67,
    t_DEL_ARROW = 68,
    t_DEL_PERIOD = 69,
    t_DEL_COMMA = 70,
    t_DEL_COLON = 71,
    t_DEL_SEMICOLON = 72,
    t_DEL_LP = 73,
    t_DEL_RP = 74,
    t_DEL_LSB = 75,
    t_DEL_RSB = 76,
    t_DEL_LCB = 77,
    t_DEL_RCB = 78
};

const int STATES_COUNT = 188;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern int SPECIAL_CASES_INDEXES[80];

extern const char *SPECIAL_CASES_KEYS[2];

extern int SPECIAL_CASES_VALUES[2];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 160;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[362][1164][2];

extern const int PRODUCTIONS[166][2];

extern const char *PARSER_ERROR[362];

} //namespace wpl

#endif
