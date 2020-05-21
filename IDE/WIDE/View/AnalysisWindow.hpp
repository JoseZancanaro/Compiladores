#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include <QDialog>
#include "../Model/Composite.hpp"

namespace Ui {
class AnalysisWindow;
}

class Analysis_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Analysis_Window(QWidget *parent = nullptr);
    ~Analysis_Window();

    void setTree(Composite<std::string> ast);

private slots:
    void dispatchClose();

private:
    Ui::AnalysisWindow *ui;
};

#endif // ANALYSISWINDOW_HPP
