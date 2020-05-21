#ifndef BIPDEFINITIONS_HPP
#define BIPDEFINITIONS_HPP

#include <string>
#include <vector>

namespace wpl::bip_asm {

struct Declaration {
    std::string id {};
    std::vector<int> default_value {};
};

struct Instruction {
    std::string op {};
    std::string operand {};
};

struct BIP_Program {
    std::vector<Declaration> data;
    std::vector<Instruction> text;
};

}



#endif // BIPDEFINITIONS_HPP
