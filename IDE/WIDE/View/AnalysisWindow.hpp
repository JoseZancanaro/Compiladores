#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include <QWidget>

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisWindow(QWidget *parent = nullptr);
    ~AnalysisWindow();

private:
    Ui::AnalysisWindow *ui;
};

#endif // ANALYSISWINDOW_HPP
