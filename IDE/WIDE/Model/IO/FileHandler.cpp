#include "FileHandler.hpp"
#include <fstream>

#include <QFile>
#include <QTextStream>

namespace wpl::io {

auto saveToFile(std::string const& path, std::string const& content) -> void {
    std::ofstream file(path);
    file << content;
    file.close();
}

auto saveToFile(std::wstring const& path, std::wstring const& content) -> void {
   QFile file(QString::fromStdWString(path));

   if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       QTextStream output(&file);
       output << content;
       file.close();
   }
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

auto loadFromFile(std::wstring const& path) -> QString {
    QFile file(QString::fromStdWString(path));

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream input(&file);
        QString content = input.readAll();
        file.close();

        return content;
    }

    return {};
}

}
