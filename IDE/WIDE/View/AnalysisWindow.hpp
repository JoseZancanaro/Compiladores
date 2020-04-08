#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include <QDialog>
#include "../Model/Composite.hpp"

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalysisWindow(QWidget *parent = nullptr);
    ~AnalysisWindow();

    void setTree(Composite<std::string> ast);

private slots:
    void dispatchClose();

private:
    Ui::AnalysisWindow *ui;
};

#endif // ANALYSISWINDOW_HPP
