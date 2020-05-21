#ifndef BIP_ASM_SYNTAX_HIGHLIGHTER_HPP
#define BIP_ASM_SYNTAX_HIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class BIP_ASM_Syntax_Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    BIP_ASM_Syntax_Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;


    QTextCharFormat instructionFormat;
    QTextCharFormat directiveFormat;
    QTextCharFormat colonFormat;
    QTextCharFormat keywordFormat;
};

#endif // BIP_ASM_SYNTAX_HIGHLIGHTER_HPP
