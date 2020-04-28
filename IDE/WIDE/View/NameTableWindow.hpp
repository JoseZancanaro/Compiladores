#ifndef NAMETABLEWINDOW_HPP
#define NAMETABLEWINDOW_HPP

#include <QDialog>

#include "../Model/Parser/Parser.hpp"

namespace Ui {
class Name_Table_Window;
}

class Name_Table_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Name_Table_Window(QWidget *parent = nullptr);

    void set_name_table(wpl::Name_Table const& name_table);

    ~Name_Table_Window();

private slots:
    void dispatch_close();

private:
    Ui::Name_Table_Window *ui;
};

#endif // NAMETABLEWINDOW_HPP
