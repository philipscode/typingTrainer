#include "trainer.h"
#include "ui_trainer.h"
#include "lessons.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <QKeyEvent>
#include <QEventLoop>
#include <QDebug>
#include <QEvent>


trainer::trainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trainer)
{
    ui->setupUi(this);
    QObject::connect(ui->startButton, SIGNAL(clicked()),
                     this, SLOT(startClicked()));
    qApp->installEventFilter(this);
}

trainer::~trainer()
{
    delete ui;
}

bool trainer::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Space)
            qDebug() << "Space!";
    }
    return QObject::eventFilter(obj, event);
}

void trainer::keyPressEvent(QKeyEvent* ke)
{
    if (ke->key() == Qt::Key_Shift) return;
    if (ke->key() == Qt::Key_Space) trainer::w = ke->text();
    trainer::w = ke->text();
    emit pressed();
}

void trainer::startClicked()
{
    ui->startButton->setEnabled(false);
    QFile inputFile(trainer::fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        trainer::errs = 0;
        QTextStream in(&inputFile);
        QString subLine = NULL;
        QString prevText = NULL;
        while (!in.atEnd())
        {
            if (trainer::flag) break;
            if (!subLine.isNull())
            {
                subLine.remove(0, 1);
                subLine.append(' ');
            }
            QString line = in.readLine();
            line.prepend(subLine);
            subLine.clear();
            for (int i = 0; (i < line.length() - 9); i++)
            {
                if (trainer::flag) break;
                subLine = line.mid(i, 10);
                if (i <= 9)
                    prevText = line.mid(0, i);
                else
                    prevText = line.mid(i - 10, 10);
                do
                {
                    if (trainer::flag) break;
                    ui->label->setText("<span style = \"color: #9F9D9D\">" + prevText + "</span>"+
                                       "<span style = \"background-color: grey; color: yellow\">" +
                                       subLine[0] + "</span>" + subLine.right(9));
                    QEventLoop loop;
                    connect(this, SIGNAL(pressed()), &loop, SLOT(quit()));
                    loop.exec();
                    if (w != subLine[0])
                    {
                        ++trainer::errs;
                        qDebug() << trainer::errs;
                    }
                } while (trainer::w != subLine[0]);
            }
        }
        subLine.remove(0, 1);
        for (int i = 0; i < subLine.length() ; i++)
        {
            if (trainer::flag) break;
            do
            {
                if (trainer::flag) break;
                ui->label->setText("<span style = \"color: #9F9D9D\">" + prevText.right(prevText.length() - i - 1) + subLine.mid(0, i) +
                                   "</span>" + "<span style = \"background-color: grey; color: yellow\">" + subLine[i] + "</span>" +
                                   subLine.right(subLine.length() - i - 1));
                QEventLoop loop;
                connect(this, SIGNAL(pressed()), &loop, SLOT(quit()));
                loop.exec();
                if ( w != subLine[i] )
                {
                    ++trainer::errs;
                    qDebug() << trainer::errs;
                }
            } while (trainer::w != subLine[i]);
        }
        qDebug() << trainer::errs;
        inputFile.close();
        trainer::flag = false;
        ui->startButton->setEnabled(true);
        ui->label->setText("Good job!");
    }
}

void trainer::on_Back_to_lesson_clicked()
{
    trainer::flag = true;
    this->close();
    trainer::fileName.clear();
    emit show_lesson_window();
}

