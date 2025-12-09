#include "markdown_parser_test.hpp"
#include "markdown_parser.hpp"
#include <QTest>
#include <QRegularExpression>

void MarkdownParserTest(){}

void MarkdownParserTest::initTestCase(){}
void MarkdownParserTest::init(){}
void MarkdownParserTest::cleanupTestCase(){}
void MarkdownParserTest::cleanup(){}

void MarkdownParserTest::testBold()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("This is **bold text** here.");
    QVERIFY(result.contains("<b>bold text</b>"));
    
    result = parser.parseToHtml("**Start** and **end**");
    QVERIFY(result.contains("<b>Start</b>"));
    QVERIFY(result.contains("<b>end</b>"));
}

void MarkdownParserTest::testItalic()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("This is *italic text* here.");
    QVERIFY(result.contains("<i>italic text</i>"));
    
    result = parser.parseToHtml("*Start* and *end*");
    QVERIFY(result.contains("<i>Start</i>"));
    QVERIFY(result.contains("<i>end</i>"));
}

void MarkdownParserTest::testUnderline()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("This is __underlined text__ here.");
    QVERIFY(result.contains("<u>underlined text</u>"));
    
    result = parser.parseToHtml("__Start__ and __end__");
    QVERIFY(result.contains("<u>Start</u>"));
    QVERIFY(result.contains("<u>end</u>"));
}

void MarkdownParserTest::testLinks()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("This is [a link](https://example.com) here.");
    QVERIFY(result.contains("<a href=\"https://example.com\">a link</a>"));
    
    result = parser.parseToHtml("[Google](https://www.google.com) and [GitHub](https://github.com)");
    QVERIFY(result.contains("<a href=\"https://www.google.com\">Google</a>"));
    QVERIFY(result.contains("<a href=\"https://github.com\">GitHub</a>"));
}

void MarkdownParserTest::testEscapeHtml()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("**Bold with <tags>** and *italic with & symbol*");
    QVERIFY(result.contains("&lt;tags&gt;"));
    QVERIFY(result.contains("&amp;"));
    
    result = parser.parseToHtml("[Link with <tags>](https://example.com)");
    QVERIFY(result.contains("&lt;tags&gt;"));
    
    result = parser.parseToHtml("__Underline with & symbol__");
    QVERIFY(result.contains("&amp;"));
}

void MarkdownParserTest::testParseToHtml()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("Simple text");
    QVERIFY(result.contains("<html>"));
    QVERIFY(result.contains("<body"));
    QVERIFY(result.contains("Simple text"));
    QVERIFY(result.contains("</body></html>"));
    
    result = parser.parseToHtml("Line 1\n\nLine 2");
    QVERIFY(result.contains("<br/>"));
    QVERIFY(result.contains("<p>Line 1</p>"));
    QVERIFY(result.contains("<p>Line 2</p>"));
}

void MarkdownParserTest::testCombinedFormatting()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("**Bold** and *italic* and __underline__");
    QVERIFY(result.contains("<b>Bold</b>"));
    QVERIFY(result.contains("<i>italic</i>"));
    QVERIFY(result.contains("<u>underline</u>"));
    
    result = parser.parseToHtml("**Bold** with [link](https://example.com)");
    QVERIFY(result.contains("<b>Bold</b>"));
    QVERIFY(result.contains("<a href=\"https://example.com\">link</a>"));
}

void MarkdownParserTest::testEmptyInput()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("");
    QVERIFY(result.contains("<html>"));
    QVERIFY(result.contains("<body"));
    QVERIFY(result.contains("</body></html>"));
    
    result = parser.parseToHtml("\n\n");
    QVERIFY(result.contains("<br/>"));
}

void MarkdownParserTest::testMultipleFormats()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("**First** **Second** **Third**");
    QVERIFY(result.contains("<b>First</b>"));
    QVERIFY(result.contains("<b>Second</b>"));
    QVERIFY(result.contains("<b>Third</b>"));
    
    result = parser.parseToHtml("*One* *Two* *Three*");
    QVERIFY(result.contains("<i>One</i>"));
    QVERIFY(result.contains("<i>Two</i>"));
    QVERIFY(result.contains("<i>Three</i>"));
    
    result = parser.parseToHtml("__First__ __Second__");
    QVERIFY(result.contains("<u>First</u>"));
    QVERIFY(result.contains("<u>Second</u>"));
}

void MarkdownParserTest::testPlainText()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("Just plain text without formatting");
    QVERIFY(result.contains("Just plain text without formatting"));
    QVERIFY(result.contains("<p>"));
    QVERIFY(!result.contains("<b>"));
    QVERIFY(!result.contains("<i>"));
    QVERIFY(!result.contains("<u>"));
}

void MarkdownParserTest::testEmptyLines()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("Line 1\n\n\nLine 2");
    int brCount = result.count("<br/>");
    QVERIFY(brCount >= 2);
    QVERIFY(result.contains("<p>Line 1</p>"));
    QVERIFY(result.contains("<p>Line 2</p>"));
    
    result = parser.parseToHtml("\nText\n");
    QVERIFY(result.contains("<br/>"));
    QVERIFY(result.contains("<p>Text</p>"));
}

void MarkdownParserTest::testEdgeCases()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("**");
    QVERIFY(!result.contains("<b>"));
    
    result = parser.parseToHtml("*");
    QVERIFY(!result.contains("<i>"));
    
    result = parser.parseToHtml("__");
    QVERIFY(!result.contains("<u>"));
    
    result = parser.parseToHtml("[]()");
    QRegularExpression linkRegex("\\[([^\\]]+)\\]\\(([^\\)]+)\\)");
    QVERIFY(!linkRegex.match("[]()").hasMatch());
    
    result = parser.parseToHtml("**bold**text");
    QVERIFY(result.contains("<b>bold</b>"));
    QVERIFY(result.contains("text"));
    
    result = parser.parseToHtml("***");
    QVERIFY(!result.contains("<b>"));
    QVERIFY(!result.contains("<i>"));
}

void MarkdownParserTest::testComplexLinks()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("[Link with spaces](https://example.com/page?param=value)");
    QVERIFY(result.contains("Link with spaces"));
    QVERIFY(result.contains("https://example.com/page?param=value"));
    
    result = parser.parseToHtml("[Text](http://site.com) and [Another](https://other.org)");
    QVERIFY(result.contains("http://site.com"));
    QVERIFY(result.contains("https://other.org"));
    
    result = parser.parseToHtml("[Link](https://example.com/path#anchor)");
    QVERIFY(result.contains("#anchor"));
}

void MarkdownParserTest::testNestedFormatting()
{
    MarkdownParser parser;
    QString result = parser.parseToHtml("**Bold** and *italic* in same line");
    QVERIFY(result.contains("<b>Bold</b>"));
    QVERIFY(result.contains("<i>italic</i>"));
    
    result = parser.parseToHtml("*Italic* and __underline__ together");
    QVERIFY(result.contains("<i>Italic</i>"));
    QVERIFY(result.contains("<u>underline</u>"));
    
    result = parser.parseToHtml("**Bold** and [link](https://example.com) and *italic*");
    QVERIFY(result.contains("<b>Bold</b>"));
    QVERIFY(result.contains("<a href=\"https://example.com\">link</a>"));
    QVERIFY(result.contains("<i>italic</i>"));
    
    result = parser.parseToHtml("[Link](https://example.com) with **bold** text");
    QVERIFY(result.contains("<a href=\"https://example.com\">Link</a>"));
    QVERIFY(result.contains("<b>bold</b>"));
}

