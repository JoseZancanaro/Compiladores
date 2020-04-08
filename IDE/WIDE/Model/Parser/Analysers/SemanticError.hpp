#ifndef SEMANTIC_ERROR_HPP
#define SEMANTIC_ERROR_HPP

#include "AnalysisError.hpp"

#include <string>

namespace wpl {

class SemanticError : public AnalysisError
{
public:

    SemanticError(const std::string &msg, int position = -1)
      : AnalysisError(msg, position) { }
};

} //namespace wpl

#endif
