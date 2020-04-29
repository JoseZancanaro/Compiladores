#ifndef SEMANTIC_TABLE_HPP
#define SEMANTIC_TABLE_HPP

#include "TypeDefinitions.hpp"
#include "OperatorDefinitions.hpp"

#include <array>

namespace wpl {

namespace detail {

constexpr std::size_t num_types = static_cast<std::size_t>(Type_Name::LAST_TYPE);
constexpr std::size_t num_operators = static_cast<std::size_t>(Operator::LAST_OPERATOR);

constexpr auto make_operation_table() -> auto {
    using Result_Type_Array = std::array<Type_Name, num_operators>;
    using Second_Type_Array = std::array<Result_Type_Array, num_types>;
    using First_Type_Array  = std::array<Second_Type_Array, num_types>;


    First_Type_Array f_param {};

    return f_param;
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

}

class SemanticTable
{
private:
    // Compile time magic
    static constexpr auto operation_table = detail::make_operation_table();
    static constexpr auto attribute_table = detail::make_type_compatibility_table();

public:
    static constexpr Type_Name get_result_type (Type_Name, Type_Name, Operator) {
      return Type_Name::INVALID;
    }

    static constexpr Type_Compatibility get_type_compatibility (Type_Name, Type_Name){
      return Type_Compatibility::NONE;
    }
};

} // namespace wpl

#endif // SEMANTIC_TABLE_HPP
