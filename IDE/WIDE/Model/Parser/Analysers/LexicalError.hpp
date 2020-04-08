#ifndef LEXICAL_ERROR_HPP
#define LEXICAL_ERROR_HPP

#include "AnalysisError.hpp"

#include <string>

namespace wpl {

class LexicalError : public AnalysisError
{
public:

    LexicalError(const std::string &msg, int position = -1)
      : AnalysisError(msg, position) { }
};

} //namespace wpl

#endif
