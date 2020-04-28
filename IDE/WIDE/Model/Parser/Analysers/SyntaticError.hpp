#ifndef SYNTATIC_ERROR_HPP
#define SYNTATIC_ERROR_HPP

#include "AnalysisError.hpp"

#include <string>

namespace wpl {

class Syntatic_Error : public Analysis_Error
{
public:

    Syntatic_Error(const std::string &msg, int position = -1)
      : Analysis_Error(msg, position) { }
};

} //namespace wpl

#endif
