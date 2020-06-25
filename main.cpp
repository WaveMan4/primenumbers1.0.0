//Name: Gilles Kepnang

#include <QtGui/QApplication>
#include "mainwindow.h"

//Create QApplication and execute
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
