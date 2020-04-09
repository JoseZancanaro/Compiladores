#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "AnalysisWindow.hpp"

#include <iostream>

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QColor>

// Control
#include "Model/Parser/Parser.hpp"
#include "Model/IO/FileHandler.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , analysisWindow(nullptr)
    , current({})
{
    ui->setupUi(this);

    /* Actions */
    /* Actions: File */
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(dispatchNew()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(dispatchOpen()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(dispatchSave()));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(dispatchSaveAs()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(dispatchQuit()));

    /* Actions: Build */
    connect(ui->actionRun, SIGNAL(triggered(bool)), this, SLOT(dispatchRun()));

    /* Actions: Tools */
    connect(ui->actionCodeAnalysis, SIGNAL(triggered(bool)), this, SLOT(dispatchCodeAnalysis()));


    /* Buttons */
    connect(ui->btnRun, SIGNAL(clicked(bool)), this, SLOT(dispatchRun()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dispatchNew()
{
    this->ui->textEdit->clear();

    QFile sample(":/sample/helloWorld.wpl");
    if (sample.open(QIODevice::ReadOnly | QIODevice::Text)) {
         QTextStream text(&sample);
         QString content = text.readAll();
         this->ui->textEdit->setPlainText(content);
    }
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

auto walk(Composite<std::string> root, std::size_t depth = 0) -> void {
    std::cout << std::string(depth * 2, ' ') << root.value << std::endl;
    for (auto const& c : root.children) {
        walk(c, depth + 1);
    }
}

void MainWindow::dispatchRun()
{
    using namespace wpl::language;

    std::string input = this->ui->textEdit->toPlainText().toStdString();
    Parser parser(input);

    auto [errors, success, tree] = parser.parse();

    this->ui->listErrors->clear();

    for (auto const& e : errors) {
        this->ui->listErrors->addItem(QString(e.getMessage()));
    }

    auto [color, message] = [status = success](){
        if (status) {
            return std::make_pair(QColor(0, 128, 0), "Compiler returned: SUCCESS.");
        } else {
            return std::make_pair(QColor(128, 0, 0), "Compiler returned: FAILURE.");
        }
    }();

    this->ui->textOut->setTextColor(color);
    this->ui->textOut->append(message);

    this->ui->tabWidget->setCurrentIndex(Tabs::COMPILER_OUTPUT);

    if (this->analysisWindow) {
        this->analysisWindow->setTree(tree.value_or(Composite<std::string>("<invalid>")));
    }
}

void MainWindow::dispatchCodeAnalysis()
{
    if (this->analysisWindow) {
        this->analysisWindow->setHidden(false);
        this->analysisWindow->activateWindow();
    }
    else {
        this->analysisWindow = new AnalysisWindow(this);
        this->analysisWindow->show();
    }
}
