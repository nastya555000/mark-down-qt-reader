#include "markdown_parser.hpp"
#include <QRegularExpression>
#include <QPair>
#include <QList>

MarkdownParser::MarkdownParser()
{
}

QString MarkdownParser::escapeHtml(const QString& text)
{
    QString result = text;
    result.replace("&", "&amp;");
    result.replace("<", "&lt;");
    result.replace(">", "&gt;");
    return result;
}

QString MarkdownParser::processBold(const QString& text)
{
    QString result = text;
    QRegularExpression regex("\\*\\*([^*]+)\\*\\*");
    QRegularExpressionMatchIterator i = regex.globalMatch(result);
    
    QList<QPair<int, int>> positions;
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        positions.append(qMakePair(match.capturedStart(0), match.capturedLength(0)));
    }
    
    for (int j = positions.size() - 1; j >= 0; --j)
    {
        QRegularExpressionMatch match = regex.match(result, positions[j].first);
        if (match.hasMatch())
        {
            QString content = match.captured(1);
            QString replacement = "<b>" + escapeHtml(content) + "</b>";
            result.replace(positions[j].first, positions[j].second, replacement);
        }
    }
    return result;
}

QString MarkdownParser::processItalic(const QString& text)
{
    QString result = text;
    QRegularExpression regex("(?<!\\*)\\*([^*]+)\\*(?!\\*)");
    QRegularExpressionMatchIterator i = regex.globalMatch(result);
    
    QList<QPair<int, int>> positions;
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        positions.append(qMakePair(match.capturedStart(0), match.capturedLength(0)));
    }
    
    for (int j = positions.size() - 1; j >= 0; --j)
    {
        QRegularExpressionMatch match = regex.match(result, positions[j].first);
        if (match.hasMatch())
        {
            QString content = match.captured(1);
            QString replacement = "<i>" + escapeHtml(content) + "</i>";
            result.replace(positions[j].first, positions[j].second, replacement);
        }
    }
    return result;
}

QString MarkdownParser::processUnderline(const QString& text)
{
    QString result = text;
    QRegularExpression regex("__(.+?)__");
    QRegularExpressionMatchIterator i = regex.globalMatch(result);
    
    QList<QPair<int, int>> positions;
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        positions.append(qMakePair(match.capturedStart(0), match.capturedLength(0)));
    }
    
    for (int j = positions.size() - 1; j >= 0; --j)
    {
        QRegularExpressionMatch match = regex.match(result, positions[j].first);
        if (match.hasMatch())
        {
            QString content = match.captured(1);
            QString replacement = "<u>" + escapeHtml(content) + "</u>";
            result.replace(positions[j].first, positions[j].second, replacement);
        }
    }
    return result;
}

QString MarkdownParser::processLinks(const QString& text)
{
    QString result = text;
    QRegularExpression regex("\\[([^\\]]+)\\]\\(([^\\)]+)\\)");
    QRegularExpressionMatchIterator i = regex.globalMatch(result);
    
    QList<QPair<int, int>> positions;
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        positions.append(qMakePair(match.capturedStart(0), match.capturedLength(0)));
    }
    
    for (int j = positions.size() - 1; j >= 0; --j)
    {
        QRegularExpressionMatch match = regex.match(result, positions[j].first);
        if (match.hasMatch())
        {
            QString linkText = match.captured(1);
            QString url = match.captured(2);
            QString htmlLink = "<a href=\"" + escapeHtml(url) + "\">" + escapeHtml(linkText) + "</a>";
            result.replace(positions[j].first, positions[j].second, htmlLink);
        }
    }
    return result;
}

QString MarkdownParser::parseToHtml(const QString& markdown)
{
    QString result = markdown;
    
    QStringList lines = result.split('\n');
    QString html = "<html><body style='font-family: Arial; padding: 10px;'>";
    
    for (const QString& line : lines)
    {
        if (line.trimmed().isEmpty())
        {
            html += "<br/>";
            continue;
        }
        
        QString processedLine = line;
        processedLine = processLinks(processedLine);
        processedLine = processBold(processedLine);
        processedLine = processItalic(processedLine);
        processedLine = processUnderline(processedLine);
        
        html += "<p>" + processedLine + "</p>";
    }
    
    html += "</body></html>";
    return html;
}

