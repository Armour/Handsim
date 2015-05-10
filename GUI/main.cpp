#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumHeight(600);
    w.setMinimumWidth(800);
    w.show();

    return a.exec();
}
