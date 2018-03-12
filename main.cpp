#include "mainwindow.h"
#include <QApplication>
#include "lessons.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Typing trainer");

    w.show();


    return a.exec();
}
