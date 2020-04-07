#include "FileHandler.hpp"
#include <fstream>

namespace wpl::io {

auto saveToFile(std::string const& path, std::string const& content) -> void {
    std::ofstream file(path);
    file << content;
}

auto loadFromFile(std::string const& path) -> std::string {
    std::ifstream file(path);
    std::string output;

    std::string line;
    while (std::getline(file, line)){
        output.append(line).append("\n");
    }

    return output;
}

}
