#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CodeEditor/CodeEditor.hpp"
#include "CodeEditor/SyntaxHighlighter.hpp"
#include "AnalysisWindow.hpp"
#include "NameTableWindow.hpp"

#include <iostream>

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QColor>

// Control
#include "Model/Parser/Parser.hpp"
#include "Model/IO/FileHandler.hpp"

namespace detail {
    auto loadText(QString const& path) -> QString {
        QFile file(path);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            return stream.readAll();
        }

        return {};
    }
}

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , codeEditor(new CodeEditor(this))
    , analysisWindow(nullptr)
    , name_table_window(nullptr)
    , current({})
{
    ui->setupUi(this);

    syntaxHighlighter = new SyntaxHighlighter(codeEditor->document());

    codeEditor->setFont(QFont("Consolas", 11, QFont::Normal));

    ui->upperSection->addWidget(codeEditor);
    ui->upperSection->setStretchFactor(1, 1);

    auto sample = detail::loadText(":/sample/helloWorld.wpl");
    this->codeEditor->setPlainText(sample);

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
    connect(ui->action_names_view, SIGNAL(triggered(bool)), this, SLOT(dispatch_names_view()));


    /* Buttons */
    connect(ui->btnRun, SIGNAL(clicked(bool)), this, SLOT(dispatchRun()));
}

Main_Window::~Main_Window()
{
    delete ui;
}

void Main_Window::dispatchNew()
{
    this->codeEditor->clear();

    auto sample = detail::loadText(":/sample/helloWorld.wpl");
    this->codeEditor->setPlainText(sample);
}

void Main_Window::dispatchOpen()
{
    QString path = QFileDialog::getOpenFileName(this, QString("Open file"));

    if (!path.isEmpty()) {
        std::string content = wpl::io::loadFromFile(path.toStdString());

        this->codeEditor->setPlainText(QString::fromStdString(content));
        this->current = path;
    }
}


void Main_Window::dispatchSave()
{
    if (this->current.has_value()) {
        wpl::io::saveToFile(this->current.value().toStdString(), codeEditor->toPlainText().toStdString());
    }
    else {
        this->dispatchSaveAs();
    }
}

void Main_Window::dispatchSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this, QString("Save file as"));

    if (!path.isEmpty()) {

        if(!path.endsWith(".wpl")) {
            path.append(".wpl");
        }

        wpl::io::saveToFile(path.toStdString(), codeEditor->toPlainText().toStdString());

        this->current = path;
    }
}

void Main_Window::dispatchQuit()
{
    QApplication::quit();
}

void Main_Window::dispatchRun()
{
    using namespace wpl::language;

    std::string input = this->codeEditor->toPlainText().toStdString();
    Parser parser(input);

    auto [errors, success, tree, names] = parser.parse();

    this->ui->listErrors->clear();

    for (auto const& e : errors) {
        this->ui->listErrors->addItem(QString(e.get_message()));
    }

    auto [color, message] = [status = success](){
        if (status) {
            return std::make_pair(QColor(0, 128, 0), "Compiler returned: SUCCESS.");
        } else {
            return std::make_pair(QColor(128, 0, 0), "Compiler returned: FAILURE.");
        }
    }();

    this->ui->textOut->setTextColor(color);
    this->ui->textOut->setText(message);

    this->ui->tabWidget->setCurrentIndex(Tabs::COMPILER_OUTPUT);

    if (this->analysisWindow) {
        this->analysisWindow->setTree(tree.value_or(Composite<std::string>("<invalid>")));
    }

    if (this->name_table_window) {
        this->name_table_window->set_name_table(names);
    }
}

void Main_Window::dispatchCodeAnalysis()
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

void Main_Window::dispatch_names_view()
{
    if (this->name_table_window) {
        this->name_table_window->setHidden(false);
        this->name_table_window->activateWindow();
    }
    else {
        this->name_table_window = new Name_Table_Window(this);
        this->name_table_window->show();
    }
}
