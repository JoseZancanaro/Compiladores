#include <iostream>
#include <QApplication>

#include "View/MainWindow.hpp"

#include "Model/IO/FileHandler.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DisableWindowContextHelpButton);
    MainWindow w;
    w.show();
    return a.exec();
}
