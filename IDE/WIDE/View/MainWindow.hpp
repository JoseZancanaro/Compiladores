#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <optional>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

private:
    Ui::MainWindow *ui;

    std::optional<QString> current;
};
#endif // MAINWINDOW_HPP
