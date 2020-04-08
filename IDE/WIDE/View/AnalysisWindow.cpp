#include "AnalysisWindow.hpp"
#include "ui_AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalysisWindow)
{
    ui->setupUi(this);

    /* Buttons */
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(dispatchClose()));
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}

void AnalysisWindow::setTree(Composite<std::string> ast)
{

}

void AnalysisWindow::dispatchClose()
{
    this->hide();
}
