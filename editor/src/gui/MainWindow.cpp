//
// Created by gmardon on 25/01/17.
//

#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    decompiler = new Decompiler();
    setupFileMenu();
    setupEditor();

    setCentralWidget(editor);
    setWindowTitle(QMainWindow::tr("Gametek Editor"));
}

void MainWindow::openGBFile(const QString &path) {
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, QMainWindow::tr("Open File"), "", "GB/GBA Files (*.gb *.gba)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            editor->setPlainText(QString::fromStdString(decompiler->decompile(fileName.toStdString())));
        }
    }
}

void MainWindow::openASMFile(const QString &path) {
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, QMainWindow::tr("Open File"), "", "ASM Files (*.asm)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            editor->setPlainText(file.readAll());
        } else {
            printf("Cannot open %s\n", fileName.toStdString().c_str());
        }
    }
}

void MainWindow::setupEditor() {
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(13);

    editor = new QTextEdit;
    editor->setFont(font);
    editor->setStyleSheet("background-color: #2c3e50;color: #ddd;");

    highlighter = new Highlighter(editor->document());
}

void MainWindow::setupFileMenu() {
    QMenu *fileMenu = new QMenu(QMainWindow::tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(QMainWindow::tr("Open .&GB/.GBA..."), this, SLOT(openGBFile()), QKeySequence::Open);
    fileMenu->addAction(QMainWindow::tr("Open .&ASM..."), this, SLOT(openASMFile()), QKeySequence::Open);
    fileMenu->addAction(QMainWindow::tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}