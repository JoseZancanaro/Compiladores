#ifndef OPERATOR_DEFINITIONS_HPP
#define OPERATOR_DEFINITIONS_HPP

namespace wpl {

enum class Operator {
    ADD  = 0,
    SUB  = 1,
    MULT = 2,
    DIV  = 3,
    REM  = 4,
    EXP  = 5,

    RELATIONAL = 6,
    LOGICAL = 7,
    BITWISE = 8,

    GT = RELATIONAL,
    LT = RELATIONAL,
    GTE = RELATIONAL,
    LTE = RELATIONAL,
    EQ  = RELATIONAL,
    NEQ = RELATIONAL,

    AND = LOGICAL,
    OR  = LOGICAL,
    NOT = LOGICAL,

    BW_SR   = BITWISE,
    BW_SL   = BITWISE,
    BW_AND  = BITWISE,
    BW_OR   = BITWISE,
    BW_COMP = BITWISE,
    BW_XOR  = BITWISE,

    FIRST_OPERATOR = ADD,
    LAST_OPERATOR = BITWISE
};

}

#endif // OPERATOR_DEFINITIONS_HPP
