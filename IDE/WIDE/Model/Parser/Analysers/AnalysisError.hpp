#ifndef ANALYSIS_ERROR_HPP
#define ANALYSIS_ERROR_HPP

#include <exception>
#include <string>

namespace wpl {

class Analysis_Error
{
public:
    Analysis_Error(const std::string &msg, int position = -1)
      : message(msg), position(position) { }

    auto get_message() const -> const char * { return message.c_str(); }
    auto get_position() const -> int { return position; }

    // virtual auto what() const noexcept -> const char * override { return get_message(); }

private:
    std::string message;
    int position;
};

} //namespace wpl

#endif
