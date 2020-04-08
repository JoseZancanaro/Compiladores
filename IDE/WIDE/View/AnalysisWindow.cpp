#include "AnalysisWindow.hpp"
#include "ui_AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalysisWindow)
{
    ui->setupUi(this);
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}
