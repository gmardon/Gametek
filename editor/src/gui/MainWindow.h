//
// Created by gmardon on 25/01/17.
//

#ifndef GAMETEK_MAINWINDOW_H
#define GAMETEK_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include <src/decompiler/Decompiler.h>
#include "Highlighter.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void openFile(const QString &path = QString());

private:
    void setupEditor();

    void setupFileMenu();

    QTextEdit *editor;
    Highlighter *highlighter;
    Decompiler *decompiler;

};


#endif //GAMETEK_MAINWINDOW_H
