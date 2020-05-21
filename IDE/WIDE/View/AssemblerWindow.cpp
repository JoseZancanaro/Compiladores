#include "AssemblerWindow.hpp"
#include "ui_AssemblerWindow.h"

#include "CodeEditor/CodeEditor.hpp"
#include "CodeEditor/BIP_ASM_SyntaxHighlighter.hpp"

#include "Model/IO/FileHandler.hpp"
#include "Model/Parser/Asm/BipDefinitions.hpp"

#include <QFileDialog>
#include <sstream>

namespace details {

auto format_program(wpl::bip_asm::BIP_Program const& program) -> std::string {
    std::stringstream ss;

    // Data
    ss << ".data" << '\n';

    for (auto const& decl : program.data) {
        ss << '\t' << decl.id << ": ";

        ss << decl.default_value.front();

        std::for_each(std::begin(decl.default_value) + 1, std::end(decl.default_value), [&ss](auto const& value) {
            ss << ", " << value;
        });

        ss << '\n';
    }

    // Text
    ss << ".text" << '\n';

    for (auto const& inst : program.text) {
        ss << '\t' << inst.op << '\t' << inst.operand << std::endl;
    }

    return ss.str();
}

}

Assembler_Window::Assembler_Window(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::Assembler_Window),
      code_editor(new Code_Editor)
{
    ui->setupUi(this);

    syntax_highlighter = new BIP_ASM_Syntax_Highlighter(code_editor->document());

    code_editor->setFont(QFont("Consolas", 11, QFont::Normal));

    ui->main_section->insertWidget(0, code_editor, 1);

    // Actions
    connect(ui->btn_save, SIGNAL(clicked(bool)), this, SLOT(dispatch_save()));
    connect(ui->btn_close, SIGNAL(clicked(bool)), this, SLOT(dispatch_close()));
}

auto Assembler_Window::set_program(wpl::bip_asm::BIP_Program program) -> void {
    this->code_editor->setPlainText(QString::fromStdString(details::format_program(program)));
}

void Assembler_Window::dispatch_save()
{
    QString path = QFileDialog::getSaveFileName(this, QString("Save file as"));

    if (!path.isEmpty()) {

        if(!path.endsWith(".asm")) {
            path.append(".asm");
        }

        wpl::io::saveToFile(path.toStdString(), code_editor->toPlainText().toStdString());
    }
}

void Assembler_Window::dispatch_close()
{
    this->hide();
}

Assembler_Window::~Assembler_Window()
{
    delete ui;
}
