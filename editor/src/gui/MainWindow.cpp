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

void MainWindow::openFile(const QString &path) {
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, QMainWindow::tr("Open File"), "", "GB/GBA Files (*.gb *.gba)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
std::cout << decompiler->decompile(fileName.toStdString());
            editor->setPlainText(QString::fromStdString(decompiler->decompile(fileName.toStdString())));
        }
    }
}

void MainWindow::setupEditor() {
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new QTextEdit;
    editor->setFont(font);

    highlighter = new Highlighter(editor->document());
}

void MainWindow::setupFileMenu() {
    QMenu *fileMenu = new QMenu(QMainWindow::tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(QMainWindow::tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(QMainWindow::tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}