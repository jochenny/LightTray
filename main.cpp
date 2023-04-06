#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "tray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    tray tray;

    return a.exec();
}
