#ifndef CODEEDITOR_HPP
#define CODEEDITOR_HPP

#include <QPlainTextEdit>

class Line_Number_Area;

class Code_Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Code_Editor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    Line_Number_Area *lineNumberArea;
};

#endif // CODEEDITOR_HPP
