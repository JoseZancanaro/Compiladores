#ifndef SEMANTIC_TABLE_HPP
#define SEMANTIC_TABLE_HPP

#include "SemanticTable_impl.hpp"

namespace wpl {

    class Semantic_Table
    {

    private:
        // Compile time magic
        static constexpr auto operation_table = detail::make_operation_table();
        static constexpr auto attribute_table = detail::make_type_compatibility_table();

    public:
        Semantic_Table() = delete;

        static constexpr Type_Name get_result_type(Type_Name left, Type_Name right, Operator op) {
            namespace d = wpl::detail;

            if (is_value_type(left) && is_value_type(right)) {
                return operation_table[d::size_cast(left)][d::size_cast(right)][d::size_cast(op)];
            }

            return Type_Name::INVALID;
        }

        static constexpr Type_Compatibility get_type_compatibility(Type_Name left, Type_Name right) {
            namespace d = wpl::detail;

            if (is_value_type(left) && is_value_type(right)) {
                return attribute_table[d::size_cast(left)][d::size_cast(right)];
            }
            if (left == Type_Name::ANY && is_value_type(right)) {
                return Type_Compatibility::FULL;
            }

            return Type_Compatibility::NONE;
        }
    };

} // namespace wpl

#endif // SEMANTIC_TABLE_HPP
