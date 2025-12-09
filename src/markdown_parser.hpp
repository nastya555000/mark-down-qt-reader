#include <QString>

class MarkdownParser
{
public:
    MarkdownParser();
    QString parseToHtml(const QString& markdown);

private:
    QString processBold(const QString& text);
    QString processItalic(const QString& text);
    QString processUnderline(const QString& text);
    QString processLinks(const QString& text);
    QString escapeHtml(const QString& text);
};

