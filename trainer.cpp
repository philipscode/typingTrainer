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
#include <QMessageBox>


trainer::trainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trainer)
{
    ui->setupUi(this);

    this->setWindowTitle("Typing trainer");

    QCursor cursor = QCursor(QPixmap(":/new/prefix3/Images/cursor.png"),0,0);
        this->setCursor(cursor);
    QCursor warn_cursor = QCursor(QPixmap(":/new/prefix3/Images/warn_cursor.png"),0,0);
        ui->Back_to_lesson->setCursor(warn_cursor);
        ui->startButton->setCursor(warn_cursor);
        ui->pauseButton->setCursor(warn_cursor);

    QObject::connect(ui->startButton, SIGNAL(clicked()),
                     this, SLOT(startClicked()));
    qApp->installEventFilter(this);
    _timer.setInterval(20);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    ui->pauseButton->setEnabled(false);
}

trainer::~trainer()
{
    delete ui;
}

void trainer::keyPressEvent(QKeyEvent* ke)
{
    if (ke->key() == Qt::Key_Shift) return;
    trainer::w = ke->text();
    emit pressed();
}

void trainer::startClicked()
{
    _lastStart = QTime::currentTime();
    _timer.start();
    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
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
                prevText.remove(0, 1);
                prevText.append(subLine[0]);
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
                if (prevText.length() == 10 && i >= 1)
                    prevText.remove(0, 1);
                if (i >= 1)
                    prevText.append(line[i-1]);
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
                        trainer::player->setMedia(QUrl("qrc:/new/prefix2/Sounds/bass1.mp3"));
                        trainer::player->setVolume(50);
                        trainer::player->play();
                        ++trainer::errs;
                        qDebug() << trainer::errs;
                    }
                } while (trainer::w != subLine[0]);
            }
        }
        prevText.remove(0, 1);
        prevText.append(subLine[0]);
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
                    trainer::player->setMedia(QUrl("qrc:/new/prefix2/Sounds/bass1.mp3"));
                    trainer::player->setVolume(50);
                    trainer::player->play();
                    ++trainer::errs;
                    qDebug() << trainer::errs;
                }
            } while (trainer::w != subLine[i]);
        }
        qDebug() << trainer::errs;
        inputFile.close();
        trainer::flag = false;
        ui->startButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        ui->label->setText("Good job!");
         _timer.stop();
    }
}
void trainer::onTimer()
{
    int mseconds = _timeLeft.msecsSinceStartOfDay() + QTime::currentTime().msecsSinceStartOfDay() - _lastStart.msecsSinceStartOfDay();
    ui->label_time->setText(QTime::fromMSecsSinceStartOfDay(mseconds).toString("mm:ss"));
}

void trainer::on_Back_to_lesson_clicked()
{
    _timer.stop();
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning", "Are you sure?", QMessageBox::Yes| QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        trainer::flag = true;
        this->close();
        trainer::fileName.clear();
        emit show_lesson_window();
    }
}

void trainer::on_pauseButton_clicked()
{
    if (_timer.isActive())
    {
        _timer.stop();
        _timeLeft = QTime::fromMSecsSinceStartOfDay(_timeLeft.msecsSinceStartOfDay() +
                                                    QTime::currentTime().msecsSinceStartOfDay() -
                                                    _lastStart.msecsSinceStartOfDay());
        ui->pauseButton->setText("Resume");
        QEventLoop loop;
        connect(ui->pauseButton, SIGNAL(clicked(bool)), &loop, SLOT(quit()));
        loop.exec();
    }
    else
    {
        _lastStart = QTime::currentTime();
        _timer.start();
        ui->pauseButton->setText("Pause");
    }
}
