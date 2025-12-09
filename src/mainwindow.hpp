#include <QWidget>

class QTextBrowser;
class QPushButton;
class QFileDialog;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();

public slots:
    void onOpenFile();
    void onFileSelected(const QString& filePath);

private:
    void setupUi();
    void loadMarkdownFile(const QString& filePath);

    QTextBrowser* m_textBrowser;
    QPushButton* m_openButton;
    QFileDialog* m_fileDialog;
};

