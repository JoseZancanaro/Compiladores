#include "BIP_ASM_SyntaxHighlighter.hpp"

BIP_ASM_Syntax_Highlighter::BIP_ASM_Syntax_Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    instructionFormat.setForeground(Qt::darkBlue);
    instructionFormat.setFontWeight(QFont::Bold);
    const QString instructionPatterns[] = {
        QStringLiteral("\\bLD\\b"), QStringLiteral("\\bLDI\\b"), QStringLiteral("\\bSTO\\b"),
        QStringLiteral("\\bADD\\b"), QStringLiteral("\\bADDI\\b"), QStringLiteral("\\bSUB\\b"),
        QStringLiteral("\\bSUBI\\b"), QStringLiteral("\\bBEQ\\b"), QStringLiteral("\\bBNE\\b"),
        QStringLiteral("\\bBGT\\b"), QStringLiteral("\\bBGE\\b"), QStringLiteral("\\bBLT\\b"),
        QStringLiteral("\\bBLE\\b"), QStringLiteral("\\bJMP\\b"), QStringLiteral("\\bAND\\b"),
        QStringLiteral("\\bANDI\\b"), QStringLiteral("\\bOR\\b"), QStringLiteral("\\bORI\\b"),
        QStringLiteral("\\bNOT\\b"), QStringLiteral("\\bSLL\\b"), QStringLiteral("\\bSRL\\b"),
        QStringLiteral("\\bSTOV\\b"), QStringLiteral("\\bLDV\\b"), QStringLiteral("\\bHLT\\b"),
        QStringLiteral("\\bCALL\\b"), QStringLiteral("\\bRETURN\\b")
    };
    for (const QString &pattern : instructionPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = instructionFormat;
        highlightingRules.append(rule);
    }

    directiveFormat.setForeground(QColor(255, 0, 255));
    directiveFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("\\.data"));
    rule.format = directiveFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegularExpression(QStringLiteral("\\.text"));
    rule.format = directiveFormat;
    highlightingRules.append(rule);

    colonFormat.setForeground(QColor(255, 0, 0));
    rule.pattern = QRegularExpression(QStringLiteral("\\:"));
    rule.format = colonFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(Qt::darkGreen);
    keywordFormat.setFontWeight(QFont::Light);
    const QString keywordPatterns[] = {
        QStringLiteral("\\$indr"), QStringLiteral("\\$in\\_port"), QStringLiteral("\\$out\\_port")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}

void BIP_ASM_Syntax_Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    //setCurrentBlockState(0);
}
