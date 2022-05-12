#include "mainwindow.h"
#include "lexicon.h"
#include <QApplication>
#include <iostream>
#include<QPixmap>
#include<QPalette>
int main(int argc, char* argv[]) {
    srand(static_cast<uint>(time(nullptr)));
    QApplication a(argc, argv);  
    MainWindow w;
    w.setWindowTitle("Boggle Game");
    w.setWindowState(Qt::WindowMaximized);
    w.setObjectName("MainWindow");
    w.show();

    return a.exec();
}
