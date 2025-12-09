#include "mainwindow.hpp"
#include "markdown_parser.hpp"
#include <QTextBrowser>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(): m_textBrowser(new QTextBrowser(this)),
                          m_openButton(new QPushButton("Открыть файл", this)),
                          m_fileDialog(new QFileDialog(this))
{
    setupUi();
    
    m_fileDialog->setNameFilter("Markdown файлы (*.md *.txt);;Все файлы (*.*)");
    m_fileDialog->setFileMode(QFileDialog::ExistingFile);
    
    connect(m_openButton, &QPushButton::clicked, this, &MainWindow::onOpenFile);
    connect(m_fileDialog, &QFileDialog::fileSelected, this, &MainWindow::onFileSelected);
}

void MainWindow::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_openButton);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(m_textBrowser);
    
    m_textBrowser->setOpenExternalLinks(true);
    
    this->setWindowTitle("Просмотрщик Markdown");
    this->resize(800, 600);
}

void MainWindow::onOpenFile()
{
    m_fileDialog->show();
}

void MainWindow::onFileSelected(const QString& filePath)
{
    loadMarkdownFile(filePath);
}

void MainWindow::loadMarkdownFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + filePath);
        return;
    }
    
    QTextStream in(&file);
    QString markdown = in.readAll();
    file.close();
    
    MarkdownParser parser;
    QString html = parser.parseToHtml(markdown);
    
    m_textBrowser->setHtml(html);
    this->setWindowTitle("Просмотрщик Markdown - " + QFileInfo(filePath).fileName());
}

