#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Code_Editor;
class WPL_Syntax_Highlighter;
class Analysis_Window;
class Name_Table_Window;
class Assembler_Window;

class Main_Window : public QMainWindow // @TODO snake_case
{
    Q_OBJECT

    enum Tabs { ISSUES, COMPILER_OUTPUT };

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
    void dispatch_bip_assembly_view();

private:
    Ui::MainWindow* ui;
    Code_Editor* codeEditor;
    WPL_Syntax_Highlighter* syntaxHighlighter;

    Analysis_Window* analysisWindow;
    Name_Table_Window* name_table_window;
    Assembler_Window* assembler_window;

    std::optional<QString> current;
};
#endif // MAINWINDOW_HPP
