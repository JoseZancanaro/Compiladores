#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <QString>
#include <string>

namespace wpl::io {

auto saveToFile(std::string const& path, std::string const& content) -> void;
auto saveToFile(std::wstring const& path, std::wstring const& content) -> void;

auto loadFromFile(std::string const& path) -> std::string;
auto loadFromFile(std::wstring const& path) -> QString;

}

#endif // FILEHANDLER_HPP
