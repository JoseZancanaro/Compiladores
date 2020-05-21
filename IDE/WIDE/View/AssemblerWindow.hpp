#ifndef ASSEMBLERWINDOW_HPP
#define ASSEMBLERWINDOW_HPP

#include <QDialog>

namespace Ui {
class Assembler_Window;
}

class Code_Editor;
class BIP_ASM_Syntax_Highlighter;

namespace wpl::bip_asm {
class BIP_Program;
}

class Assembler_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Assembler_Window(QWidget *parent = nullptr);
    ~Assembler_Window();

    auto set_program(wpl::bip_asm::BIP_Program program) -> void;

private slots:
    void dispatch_save();
    void dispatch_close();

private:
    Ui::Assembler_Window* ui;
    Code_Editor* code_editor;
    BIP_ASM_Syntax_Highlighter* syntax_highlighter;
};

#endif // ASSEMBLERWINDOW_HPP
