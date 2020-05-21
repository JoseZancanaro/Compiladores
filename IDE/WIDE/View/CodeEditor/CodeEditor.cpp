#include "CodeEditor.hpp"

#include "Line_Number_Area.hpp"

#include <QPainter>
#include <QTextBlock>
#include <QDebug>

Code_Editor::Code_Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new Line_Number_Area(this);

    connect(this, &Code_Editor::blockCountChanged, this, &Code_Editor::updateLineNumberAreaWidth);
    connect(this, &Code_Editor::updateRequest, this, &Code_Editor::updateLineNumberArea);
    connect(this, &Code_Editor::cursorPositionChanged, this, &Code_Editor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int Code_Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    auto qty = qMax(digits, 2);

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * qty;

    return space + this->lineNumberArea->getPadding();
}

void Code_Editor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void Code_Editor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void Code_Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void Code_Editor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(211, 234, 251);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void Code_Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(240, 240, 240));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(153, 153, 153));
            painter.drawText(0, top, lineNumberArea->width() - lineNumberArea->getPadding() + 6, fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
