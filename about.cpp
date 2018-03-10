#include "about.h"
#include "ui_about.h"
#include "mainwindow.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
}

about::~about()
{
    delete ui;
}

void about::on_GoBack_clicked()
{
    this->close();
    emit main_window();
}