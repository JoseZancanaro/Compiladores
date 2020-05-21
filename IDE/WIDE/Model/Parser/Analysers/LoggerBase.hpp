#ifndef LOGGER_BASE_HPP
#define LOGGER_BASE_HPP

#include <string>

class Logger_Base {
public:
    virtual auto log(std::string const& content) -> void = 0;
    virtual ~Logger_Base() = default;
};

class Null_Logger : public Logger_Base {
    auto log([[maybe_unused]] std::string const& content) -> void override {}
};

#endif // LOGGER_BASE_HPP
