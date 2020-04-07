#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QFileDialog>

// Control
#include "Model/IO/FileHandler.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , current({})
{
    ui->setupUi(this);

    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(dispatchNew()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(dispatchOpen()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(dispatchSave()));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(dispatchSaveAs()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(dispatchQuit()));

    // Where is Zé?
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dispatchNew()
{
    this->ui->textEdit->clear();
}

void MainWindow::dispatchOpen()
{
    QString path = QFileDialog::getOpenFileName(this, QString("Open file"));

    if (!path.isEmpty()) {
        std::string content = wpl::io::loadFromFile(path.toStdString());

        this->ui->textEdit->setPlainText(QString::fromStdString(content));
        this->current = path;
    }
}


void MainWindow::dispatchSave()
{
    if (this->current.has_value()) {
        wpl::io::saveToFile(this->current.value().toStdString(), ui->textEdit->toPlainText().toStdString());
    }
    else {
        this->dispatchSaveAs();
    }
}

void MainWindow::dispatchSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this, QString("Save file as"));

    if (!path.isEmpty()) {

        if(!path.endsWith(".wpl")) {
            path.append(".wpl");
        }

        wpl::io::saveToFile(path.toStdString(), this->ui->textEdit->toPlainText().toStdString());

        this->current = path;
    }
}

void MainWindow::dispatchQuit()
{
    QApplication::quit();
}

