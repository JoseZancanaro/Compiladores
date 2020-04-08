#ifndef ANALYSIS_ERROR_HPP
#define ANALYSIS_ERROR_HPP

#include <string>

namespace wpl {

class AnalysisError
{
public:

    AnalysisError(const std::string &msg, int position = -1)
      : message(msg), position(position) { }

    const char *getMessage() const { return message.c_str(); }
    int getPosition() const { return position; }

private:
    std::string message;
    int position;
};

} //namespace wpl

#endif
