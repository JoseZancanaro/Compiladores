#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <optional>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CodeEditor;
class SyntaxHighlighter;
class AnalysisWindow;
class Name_Table_Window;

class Main_Window : public QMainWindow // @TODO snake_case
{
    Q_OBJECT

    enum Tabs { ERRORS, WARNINGS, COMPILER_OUTPUT };

public:
    Main_Window(QWidget *parent = nullptr);
    ~Main_Window();

private slots:
    void dispatchNew();
    void dispatchOpen();
    void dispatchSave();
    void dispatchSaveAs();
    void dispatchQuit();
    void dispatchRun();
    void dispatchCodeAnalysis();
    void dispatch_names_view();

private:
    Ui::MainWindow* ui;
    CodeEditor* codeEditor;
    SyntaxHighlighter* syntaxHighlighter;

    AnalysisWindow* analysisWindow;
    Name_Table_Window* name_table_window;

    std::optional<QString> current;
};
#endif // MAINWINDOW_HPP
