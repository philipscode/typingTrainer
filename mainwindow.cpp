#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Typing trainer");

    QCursor cursor = QCursor(QPixmap(":/new/prefix3/Images/cursor.png"),0,0);
        this->setCursor(cursor);
    QCursor quest_cursor = QCursor(QPixmap(":/new/prefix3/Images/quest_cursor.png"),0,0);
        ui->About->setCursor(quest_cursor);

    QCursor warn_cursor = QCursor(QPixmap(":/new/prefix3/Images/warn_cursor.png"),0,0);
        ui->Begin->setCursor(warn_cursor);
        ui->Exit->setCursor(warn_cursor);

    lesson_window = new lessons();
    about_window = new about(this);
    connect (lesson_window, &lessons::main_window, this, &MainWindow::show);
    connect(about_window, &about::main_window, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_Begin_clicked()
{
    this->close();
    lesson_window->show();
}

void MainWindow::on_About_clicked()
{
    this->close();
    about_window->show();
}

void MainWindow::on_Exit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning", "Are you sure?", QMessageBox::Yes| QMessageBox::No);
    if (reply == QMessageBox::Yes){
     QApplication::quit();
    }
}

