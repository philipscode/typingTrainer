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

