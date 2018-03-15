#include "mainwindow.h"
#include <QApplication>
#include "lessons.h"
#include <QFontDatabase>

int main(int argc, char *argv[])
{  
    QApplication a(argc, argv);
    MainWindow w;
    QFontDatabase::addApplicationFont(":/new/prefix4/Indie_Flower/IndieFlower.ttf");

    w.setWindowTitle("Typing trainer");

    w.show();

    return a.exec();
}
