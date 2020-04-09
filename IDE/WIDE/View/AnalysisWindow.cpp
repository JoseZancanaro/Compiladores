#include "AnalysisWindow.hpp"
#include "ui_AnalysisWindow.h"

#include <queue>

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
    using TreePair = std::pair<Composite<std::string>, QTreeWidgetItem*>;
    std::queue<TreePair> builder;

    auto rootWidget = new QTreeWidgetItem();

    builder.push({ ast, rootWidget });

    while (!builder.empty()) {
        auto & [composite, widget] = builder.front();

        widget->setText(0, QString::fromStdString(composite.value));

        for (auto const & c : composite.children) {
            auto child = new QTreeWidgetItem(widget);

            widget->addChild(child);
            builder.push({ c, child });
        }

        builder.pop();
    }

    this->ui->treeWidget->clear();
    this->ui->treeWidget->insertTopLevelItem(0, rootWidget);
}

void AnalysisWindow::dispatchClose()
{
    this->hide();
}
