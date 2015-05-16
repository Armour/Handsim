#include <QApplication>
#include "mainwindow.h"
#include "mmu.h"

MMU mmu;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumHeight(700);
    w.setMinimumWidth(1360);
    //w.showMaximized();
    w.show();
    return a.exec();
}
