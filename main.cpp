#include "mainwindow.h"

#include <QApplication>
#include <QUdpSocket>
#include <QHostAddress>
#include <QLibrary>
#include <QSharedMemory>
#include <QCoreApplication>
//#include "focusform.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
