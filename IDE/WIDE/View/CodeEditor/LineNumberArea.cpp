#include "LineNumberArea.hpp"

#include "CodeEditor.hpp"

LineNumberArea::LineNumberArea(CodeEditor *editor)
    : QWidget(editor), codeEditor(editor), padding(20)
{}

QSize LineNumberArea::sizeHint() const
{
    return QSize(this->codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    this->codeEditor->lineNumberAreaPaintEvent(event);
}

int LineNumberArea::getPadding() const
{
    return this->padding;
}
