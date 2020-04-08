#ifndef SYNTATIC_ERROR_HPP
#define SYNTATIC_ERROR_HPP

#include "AnalysisError.hpp"

#include <string>

namespace wpl {

class SyntaticError : public AnalysisError
{
public:

    SyntaticError(const std::string &msg, int position = -1)
      : AnalysisError(msg, position) { }
};

} //namespace wpl

#endif
