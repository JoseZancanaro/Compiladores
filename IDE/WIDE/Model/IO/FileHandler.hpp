#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>

namespace wpl::io {

auto saveToFile(std::string const& path, std::string const& content) -> void;
auto loadFromFile(std::string const& path) -> std::string;

}

#endif // FILEHANDLER_HPP
