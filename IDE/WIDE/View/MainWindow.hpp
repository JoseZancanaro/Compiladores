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

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Tabs { ERRORS, WARNINGS, COMPILER_OUTPUT };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void dispatchNew();
    void dispatchOpen();
    void dispatchSave();
    void dispatchSaveAs();
    void dispatchQuit();
    void dispatchRun();
    void dispatchCodeAnalysis();

private:
    Ui::MainWindow *ui;
    CodeEditor *codeEditor;
    SyntaxHighlighter *syntaxHighlighter;

    AnalysisWindow *analysisWindow;

    std::optional<QString> current;
};
#endif // MAINWINDOW_HPP
