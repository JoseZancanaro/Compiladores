#include "Line_Number_Area.hpp"

#include "CodeEditor.hpp"

Line_Number_Area::Line_Number_Area(Code_Editor *editor)
    : QWidget(editor), codeEditor(editor), padding(20)
{}

QSize Line_Number_Area::sizeHint() const
{
    return QSize(this->codeEditor->lineNumberAreaWidth(), 0);
}

void Line_Number_Area::paintEvent(QPaintEvent *event)
{
    this->codeEditor->lineNumberAreaPaintEvent(event);
}

int Line_Number_Area::getPadding() const
{
    return this->padding;
}
