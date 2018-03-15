#include "about.h"
#include "ui_about.h"
#include "mainwindow.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    this->setWindowTitle("Typing trainer");

    QCursor cursor = QCursor(QPixmap(":/new/prefix3/Images/cursor.png"),0,0);
    this->setCursor(cursor);

    QCursor warn_cursor = QCursor(QPixmap(":/new/prefix3/Images/warn_cursor.png"),0,0);
    ui->GoBack->setCursor(warn_cursor);

    setWindowIcon(QIcon(":/new/prefix3/Images/icon.png"));
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
