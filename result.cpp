#include "result.h"
#include "ui_result.h"
#include "trainer.h"
#include "mainwindow.h"

result::result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);

    this->setWindowTitle("Typing trainer");

    setWindowIcon(QIcon(":/new/prefix3/Images/icon.png"));

    QCursor cursor = QCursor(QPixmap(":/new/prefix3/Images/cursor.png"),0,0);
    this->setCursor(cursor);

    QCursor warn_cursor = QCursor(QPixmap(":/new/prefix3/Images/warn_cursor.png"),0,0);
    ui->backButton->setCursor(warn_cursor);
}

result::~result()
{
    delete ui;
}

void result::setResult()
{
    ui->symbolsLabel->setNum(result::symbols);
    ui->errsLabel->setNum(result::errs);
    ui->timeLabel->setText(QString::number(result::time) + " сек");
    ui->speedLabel->setText(QString::number(int(result::symbols / (result:: time / 60))) + " сим/мин");
}

void result::on_backButton_clicked()
{
    this->close();
}
