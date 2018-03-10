#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lessons.h"
#include "about.h"
#include "trainer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
    void pressed();
    void clicked();

public slots:



private slots:

    void on_Begin_clicked();

    void on_About_clicked();

    void on_Exit_clicked();

private:
    Ui::MainWindow * ui;
    lessons * lesson_window;
    about * about_window;

};

#endif // MAINWINDOW_H
