#ifndef TYPE_DEFINITIONS_HPP
#define TYPE_DEFINITIONS_HPP

#include <string>

namespace wpl
{

enum class Type_Name {
    UNKNOWN = 100,
    INVALID = 101,
    VOID = 102,
    ANY = 103,
    INTEGER = 0,
    FLOAT = 1,
    DOUBLE = 2,
    BOOL = 3,
    CHAR = 4,
    STRING = 5,
    FIRST_TYPE = INTEGER,
    LAST_TYPE = STRING
};

enum class Type_Compatibility {
    FULL = 0,
    NARROWING = 1,
    NONE = 2
};

struct Type {
    Type_Name name;

    // Type Flags
    bool array {};
    bool pointer {};
    bool ref {};
    bool constant {};
};

namespace type_traits {
    constexpr auto is_primitive(Type const& type) -> bool {
        return type.array == false && type.pointer == false;
    }

    constexpr auto is_primitive_integral(Type const& type) -> bool {
        return type.name == Type_Name::INTEGER;
    }

    constexpr auto is_primitive_floating_point(Type const& type) -> bool {
        return type.name == Type_Name::FLOAT || type.name == Type_Name::DOUBLE;
    }

    constexpr auto is_primitive_numeric(Type const& type) -> bool {
        return is_primitive_integral(type) || is_primitive_floating_point(type);
    }

    constexpr auto is_primitive_truthy_type(Type const& type) -> bool {
        return is_primitive_numeric(type) || type.name == Type_Name::BOOL;
    }

    constexpr auto is_integral(Type const& type) -> bool {
        return is_primitive_integral(type) && is_primitive(type);
    }

    constexpr auto is_floating_point(Type const& type) -> bool {
        return is_primitive_floating_point(type) && is_primitive(type);
    }

    constexpr auto is_numeric(Type const& type) -> bool {
        return is_primitive_numeric(type) && is_primitive(type);
    }

    constexpr auto is_truthy_type(Type const& type) -> bool {
        return is_primitive_truthy_type(type) && is_primitive(type);
    }
}

auto get_type_description(Type_Name type) -> std::string;
auto get_type_name(std::string const& name) -> Type_Name;

constexpr auto is_value_type(Type_Name const& type) -> bool {
    return type >= Type_Name::FIRST_TYPE && type <= Type_Name::LAST_TYPE;
};

}

#endif // TYPE_DEFINITIONS_HPP
