#include <QObject>

class MarkdownParserTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();

    void testBold();
    void testItalic();
    void testUnderline();
    void testLinks();
    void testEscapeHtml();
    void testParseToHtml();
    void testCombinedFormatting();
    void testEmptyInput();
    void testMultipleFormats();
    void testPlainText();
    void testEmptyLines();
    void testEdgeCases();
    void testComplexLinks();
    void testNestedFormatting();

    void cleanupTestCase();
    void cleanup();
};

