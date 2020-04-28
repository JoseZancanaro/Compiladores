#include "NameTableWindow.hpp"
#include "ui_NameTableWindow.h"

#include <QTableWidgetItem>

#include <array>

namespace detail {

auto make_table_widget_item(std::string const& text) -> QTableWidgetItem* {
    return new QTableWidgetItem(QString::fromStdString(text));
}

auto make_table_widget_item(bool flag) -> QTableWidgetItem* {
    if (flag) {
        return new QTableWidgetItem(QString("true"));
    }
    else {
        return new QTableWidgetItem(QString("false"));
    }
}

auto make_table_widget_item(std::size_t number) -> QTableWidgetItem* {
    return new QTableWidgetItem(QString::number(number));
}

}

Name_Table_Window::Name_Table_Window(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::Name_Table_Window)
{
    ui->setupUi(this);

    // Close event
    connect(this->ui->bt_close, SIGNAL(clicked(bool)), this, SLOT(dispatch_close()));
}

void Name_Table_Window::set_name_table(wpl::Name_Table const& name_table)
{
    this->ui->name_table_widget->reset();
    this->ui->name_table_widget->setRowCount(0);

    for (auto const& name : name_table) {
        auto row_count = this->ui->name_table_widget->rowCount();
        this->ui->name_table_widget->insertRow(row_count);

        std::array columns {
            detail::make_table_widget_item(name.scope),
            detail::make_table_widget_item(name.id),
            detail::make_table_widget_item(name.type.name),
            detail::make_table_widget_item(name.inferred.name),
            detail::make_table_widget_item(name.initialized),
            detail::make_table_widget_item(name.read),
            detail::make_table_widget_item(name.param),
            detail::make_table_widget_item(name.function),
            detail::make_table_widget_item(name.type.array),
            detail::make_table_widget_item(name.type.constant),
            detail::make_table_widget_item(name.type.ref),
            detail::make_table_widget_item(name.type.pointer)
        };

        auto column_number = 0;
        for (auto const& column : columns) {
            this->ui->name_table_widget->setItem(row_count, column_number++, column);
        }
    }
}

void Name_Table_Window::dispatch_close()
{
    this->hide();
}

Name_Table_Window::~Name_Table_Window()
{
    delete ui;
}
