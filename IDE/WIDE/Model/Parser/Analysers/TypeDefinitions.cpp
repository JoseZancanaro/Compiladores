#include "TypeDefinitions.hpp"

namespace wpl {

auto get_type_description(Type_Name type) -> std::string  {
    switch (type) {
    case Type_Name::UNKNOWN: return "Unknown";
    case Type_Name::INVALID: return "Invalid";
    case Type_Name::VOID:    return "Void";
    case Type_Name::ANY:     return "Any";
    case Type_Name::INTEGER: return "Integer";
    case Type_Name::FLOAT:   return "Float";
    case Type_Name::DOUBLE:  return "Double";
    case Type_Name::BOOL:    return "Bool";
    case Type_Name::CHAR:    return "Char";
    case Type_Name::STRING:  return "String";
    default:                 return "Unknown";
    }
}

auto get_type_name(std::string const& name) -> Type_Name {
    if (name == "Unknown") { return Type_Name::UNKNOWN; }
    if (name == "Invalid") { return Type_Name::INVALID; }
    if (name == "Void")    { return Type_Name::VOID;    }
    if (name == "Any")     { return Type_Name::ANY;     }
    if (name == "Integer") { return Type_Name::INTEGER; }
    if (name == "Float")   { return Type_Name::FLOAT;   }
    if (name == "Double")  { return Type_Name::DOUBLE;  }
    if (name == "Bool")    { return Type_Name::BOOL;    }
    if (name == "Char")    { return Type_Name::CHAR;    }
    if (name == "String")  { return Type_Name::STRING;  }
    return Type_Name::UNKNOWN;
}

auto to_string(Type const& type) -> std::string {
    std::string vector = type.array ? "[]" : "";
    std::string constant = type.constant ? " const" : "";
    std::string ref = type.ref ? "&" : "";
    std::string pointer = type.pointer ? "*" : "";

    return get_type_description(type.name) + vector + constant + ref + pointer;
};

}
