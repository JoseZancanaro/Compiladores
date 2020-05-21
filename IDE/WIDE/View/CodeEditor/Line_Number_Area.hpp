#ifndef LINENUMBERAREA_HPP
#define LINENUMBERAREA_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class Code_Editor;

class Line_Number_Area : public QWidget
{
    Q_OBJECT
public:
    explicit Line_Number_Area(Code_Editor *editor);

    QSize sizeHint() const override;

    int getPadding() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Code_Editor *codeEditor;
    int padding;
};

#endif // LINENUMBERAREA_HPP
