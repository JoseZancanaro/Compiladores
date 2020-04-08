#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include <QDialog>

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalysisWindow(QWidget *parent = nullptr);
    ~AnalysisWindow();

private:
    Ui::AnalysisWindow *ui;
};

#endif // ANALYSISWINDOW_HPP
