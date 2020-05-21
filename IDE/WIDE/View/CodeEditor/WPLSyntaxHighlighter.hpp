#ifndef SYNTAXHIGHLIGHTER_HPP
#define SYNTAXHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class WPL_Syntax_Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    WPL_Syntax_Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;


    QTextCharFormat keywordFormat;
    QTextCharFormat quotationFormat;
};

#endif // SYNTAXHIGHLIGHTER_HPP
