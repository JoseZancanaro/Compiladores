#include <iostream>
#include <QApplication>

#include "View/MainWindow.hpp"

#include "Model/IO/FileHandler.hpp"

#include "Model/Parser/Analysers/SemanticTable.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DisableWindowContextHelpButton);

    Main_Window w;
    w.show();
    return a.exec();
}
