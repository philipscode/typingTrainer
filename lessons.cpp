#include "lessons.h"
#include "ui_lessons.h"
#include "mainwindow.h"
#include <QDebug>

lessons::lessons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lessons)
{
    ui->setupUi(this);

    this->setWindowTitle("Typing trainer");

    QCursor cursor = QCursor(QPixmap(":/new/prefix3/Images/cursor.png"),0,0);
        this->setCursor(cursor);
    QCursor warn_cursor = QCursor(QPixmap(":/new/prefix3/Images/warn_cursor.png"),0,0);
        ui->Back_to_menu->setCursor(warn_cursor);
        ui->lesson_1->setCursor(warn_cursor);
        ui->lesson_2->setCursor(warn_cursor);
        ui->lesson_3->setCursor(warn_cursor);
        ui->lesson_4->setCursor(warn_cursor);
        ui->lesson_5->setCursor(warn_cursor);

    connect(this, SIGNAL(file_name(QString)),this, SLOT(start_lesson(QString)));
}

lessons::~lessons()
{
    delete ui;
}

void lessons::on_Back_to_menu_clicked()
{
    this->close();
    emit main_window();
}

void lessons::start_lesson(QString s)
{
    this->close();
    trainer_window = new trainer();
    connect(trainer_window, &trainer::show_lesson_window, this, &lessons::show);
    trainer_window->fileName = s;
    trainer_window->show();
    this->hide();
}

void lessons::on_lesson_1_clicked()
{
    emit file_name(":/new/prefix1/Files/lorem1.txt");
}

void lessons::on_lesson_2_clicked()
{
    emit file_name(":/new/prefix1/Files/lorem2.txt");
}

void lessons::on_lesson_3_clicked()
{
    emit file_name(":/new/prefix1/Files/lorem3.txt");
}

void lessons::on_lesson_4_clicked()
{
    emit file_name(":/new/prefix1/Files/lorem4.txt");
}

void lessons::on_lesson_5_clicked()
{
    emit file_name(":/new/prefix1/Files/lorem5.txt");
}
