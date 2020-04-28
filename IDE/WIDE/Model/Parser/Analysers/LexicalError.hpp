#ifndef LEXICAL_ERROR_HPP
#define LEXICAL_ERROR_HPP

#include "AnalysisError.hpp"

#include <string>

namespace wpl {

class Lexical_Error : public Analysis_Error
{
public:
    Lexical_Error(const std::string &msg, int position = -1)
      : Analysis_Error(msg, position) { }
};

} //namespace wpl

#endif
