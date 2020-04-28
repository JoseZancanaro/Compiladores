#ifndef SEMANTIC_ERROR_HPP
#define SEMANTIC_ERROR_HPP

#include "AnalysisError.hpp"

#include <string>

namespace wpl {

class Semantic_Error : public Analysis_Error
{
public:
    Semantic_Error(const std::string &msg, int position = -1)
      : Analysis_Error(msg, position) { }
};

} //namespace wpl

#endif
