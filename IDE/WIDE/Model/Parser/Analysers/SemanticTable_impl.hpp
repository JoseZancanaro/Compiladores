#ifndef SEMANTIC_TABLE_IMPL_HPP
#define SEMANTIC_TABLE_IMPL_HPP

#include "TypeDefinitions.hpp"
#include "OperatorDefinitions.hpp"

#include <array>

namespace wpl::detail {

    using Op = Operator;
    using Tn = Type_Name;

    constexpr std::size_t num_types = static_cast<std::size_t>(Tn::LAST_TYPE) + 1;
    constexpr std::size_t num_operators = static_cast<std::size_t>(Op::LAST_OPERATOR) + 1;

    using Result_Type_Array = std::array<Tn, num_operators>;
    using Second_Type_Array = std::array<Result_Type_Array, num_types>;
    using First_Type_Array  = std::array<Second_Type_Array, num_types>;

    template <typename Container>
    constexpr auto make_filled_container(typename Container::value_type value) -> Container {
        Container container {};

        for (auto & i : container) {
            i = value;
        }

        return container;
    }

    // Cast type enum into std::size_t
    constexpr auto size_cast(Tn tn) -> std::size_t {
        return static_cast<std::size_t>(tn);
    }

    // Cast operator enum into std::size_t
    constexpr auto size_cast(Op op) -> std::size_t {
        return static_cast<std::size_t>(op);
    }

    constexpr auto make_operation_table() -> auto {
        auto all_invalid = make_filled_container<Result_Type_Array>(Tn::INVALID);

        /* L:INTEGER */
        Second_Type_Array integer_results {{
                           /*    ADD          SUB          MULT         DIV          REM           EXP        REL       LOGIC      BITWISE   */
            /* R:INTEGER */ { Tn::INTEGER, Tn::INTEGER, Tn::INTEGER, Tn::FLOAT,   Tn::INTEGER, Tn::INTEGER, Tn::BOOL, Tn::BOOL, Tn::INTEGER },
            /* R:FLOAT   */ { Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::INVALID, Tn::FLOAT,   Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:DOUBLE  */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::DOUBLE,  Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:BOOL    */ { Tn::INTEGER, Tn::INTEGER, Tn::INTEGER, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:CHAR    */ all_invalid,
            /* R:STRING  */ all_invalid,
        }};

        /* L:FLOAT */
        Second_Type_Array float_results {{
                           /*    ADD          SUB          MULT         DIV          REM           EXP        REL       LOGIC      BITWISE   */
            /* R:INTEGER */ { Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::INVALID, Tn::FLOAT,   Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:FLOAT   */ { Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::INVALID, Tn::FLOAT,   Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:DOUBLE  */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::DOUBLE,  Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:BOOL    */ { Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:CHAR    */ all_invalid,
            /* R:STRING  */ all_invalid,
        }};

        /* L:DOUBLE */
        Second_Type_Array double_results {{
                           /*    ADD          SUB          MULT         DIV          REM           EXP        REL       LOGIC      BITWISE   */
            /* R:INTEGER */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::DOUBLE,  Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:FLOAT   */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::DOUBLE,  Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:DOUBLE  */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::DOUBLE,  Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:BOOL    */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:CHAR    */ all_invalid,
            /* R:STRING  */ all_invalid,
        }};

        /* L:BOOL */
        Second_Type_Array bool_results {{
                           /*    ADD          SUB          MULT         DIV          REM           EXP        REL       LOGIC      BITWISE   */
            /* R:INTEGER */ { Tn::INTEGER, Tn::INTEGER, Tn::INTEGER, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:FLOAT   */ { Tn::FLOAT,   Tn::FLOAT,   Tn::FLOAT,   Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:DOUBLE  */ { Tn::DOUBLE,  Tn::DOUBLE,  Tn::DOUBLE,  Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:BOOL    */ { Tn::INTEGER, Tn::INTEGER, Tn::INTEGER, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL, Tn::BOOL, Tn::INVALID },
            /* R:CHAR    */ all_invalid,
            /* R:STRING  */ all_invalid,
        }};

        /* L:CHAR */
        Second_Type_Array char_results {{
                           /*    ADD          SUB          MULT         DIV          REM           EXP        REL           LOGIC      BITWISE   */
            /* R:INTEGER */ all_invalid,
            /* R:FLOAT   */ all_invalid,
            /* R:DOUBLE  */ all_invalid,
            /* R:BOOL    */ all_invalid,
            /* R:CHAR    */ { Tn::STRING,  Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL,    Tn::INVALID, Tn::INVALID },
            /* R:STRING  */ { Tn::STRING,  Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID },
        }};

        /* L:STRING */
        Second_Type_Array string_results {{
                           /*    ADD          SUB          MULT         DIV          REM           EXP        REL           LOGIC      BITWISE   */
            /* R:INTEGER */ all_invalid,
            /* R:FLOAT   */ all_invalid,
            /* R:DOUBLE  */ all_invalid,
            /* R:BOOL    */ all_invalid,
            /* R:CHAR    */ { Tn::STRING,  Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID },
            /* R:STRING  */ { Tn::STRING,  Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::INVALID, Tn::BOOL,    Tn::INVALID, Tn::INVALID },
        }};

        First_Type_Array first {
            integer_results, float_results, double_results, bool_results, char_results, string_results
        };

        return first;
    };

    constexpr auto make_type_compatibility_table() -> auto {
        using tc = Type_Compatibility;

        return std::array {        /*  INTEGER      FLOAT         DOUBLE        BOOL       CHAR    STRING  */
            /* INTEGER */ std::array {tc::FULL, tc::NARROWING, tc::NARROWING, tc::FULL, tc::NONE, tc::NONE},
            /* FLOAT   */ std::array {tc::FULL, tc::FULL,      tc::NARROWING, tc::FULL, tc::NONE, tc::NONE},
            /* DOUBLE  */ std::array {tc::FULL, tc::FULL,      tc::FULL,      tc::FULL, tc::NONE, tc::NONE},
            /* BOOL    */ std::array {tc::FULL, tc::FULL,      tc::FULL,      tc::FULL, tc::NONE, tc::NONE},
            /* CHAR    */ std::array {tc::NONE, tc::NONE,      tc::NONE,      tc::NONE, tc::FULL, tc::NONE},
            /* STRING  */ std::array {tc::NONE, tc::NONE,      tc::NONE,      tc::NONE, tc::NONE, tc::FULL},
        };
    }

} // namespace wpl::detail

#endif // SEMANTIC_TABLE_IMPL_HPP
