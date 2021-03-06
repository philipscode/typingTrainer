#include "trainer.h"
#include "ui_trainer.h"
#include "lessons.h"
#include "result.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <QKeyEvent>
#include <QEventLoop>
#include <QDebug>
#include <QEvent>
#include <QMessageBox>
#include <QFont>


trainer::trainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trainer)
{
    ui->setupUi(this);

    this->setWindowTitle("Typing trainer");

    setWindowIcon(QIcon(":/new/prefix3/Images/icon.png"));

    QCursor cursor = QCursor(QPixmap(":/new/prefix3/Images/cursor.png"),0,0);
    this->setCursor(cursor);

    QCursor warn_cursor = QCursor(QPixmap(":/new/prefix3/Images/warn_cursor.png"),0,0);

    ui->Back_to_lesson->setCursor(warn_cursor);
    ui->startButton->setCursor(warn_cursor);
    ui->pauseButton->setCursor(warn_cursor);

    QObject::connect(ui->startButton, SIGNAL(clicked()),
                     this, SLOT(startClicked()));
    _timer.setInterval(20);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    ui->pauseButton->setEnabled(false);
    connect(this, SIGNAL(finished(int, int, int)), this, SLOT(showResult(int, int, int)));
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
    QFont font;
    font.setFamily("Georgia");
    font.setPixelSize(24);
    font.setBold(false);
    ui->label->setFont(font);
    ui->startButton->setText("Start");
    _lastStart = QTime::currentTime();
    _timer.start();
    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    QFile inputFile(trainer::fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        trainer::errs = 0;
        trainer::length = 0;
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
            trainer::length += line.length();
            line.prepend(subLine);
            subLine.clear();
            for (int i = 0; (i < line.length() - 19); i++)
            {
                if (trainer::flag) break;
                subLine = line.mid(i, 20);
                if (prevText.length() == 20 && i >= 1)
                    prevText.remove(0, 1);
                if (i >= 1)
                    prevText.append(line[i-1]);
                do
                {
                    if (trainer::flag) break;
                    ui->label->setText("<span style = \"color: #9F9D9D\">" + prevText + "</span>"+
                                       "<span style = \"background-color: rgb(191, 191, 191); color: rgb(230, 255, 139)\">" +
                                       subLine[0] + "</span>" + subLine.right(19));
                    QEventLoop loop;
                    connect(this, SIGNAL(pressed()), &loop, SLOT(quit()));
                    loop.exec();
                    if (w != subLine[0])
                    {
                        trainer::player->setMedia(QUrl("qrc:/new/prefix2/Sounds/clap.mp3"));
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
                                   "</span>" + "<span style = \"background-color: rgb(191, 191, 191); color: rgb(230, 255, 139)\">" +
                                   subLine[i] + "</span>" + subLine.right(subLine.length() - i - 1));
                QEventLoop loop;
                connect(this, SIGNAL(pressed()), &loop, SLOT(quit()));
                loop.exec();
                if ( w != subLine[i] )
                {
                    trainer::player->setMedia(QUrl("qrc:/new/prefix2/Sounds/clap.mp3"));
                    trainer::player->setVolume(50);
                    trainer::player->play();
                    ++trainer::errs;
                    qDebug() << trainer::errs;
                }
            } while (trainer::w != subLine[i]);
        }
        qDebug() << length << ' ' << errs << ' ' << time;
        inputFile.close();
        trainer::flag = false;
        ui->startButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        ui->label->setText("Good job!");
        QFont font;
        font.setFamily("Indie Flower");
        font.setPointSize(30);
        font.setBold(true);
        ui->label->setFont(font);

         _timer.stop();
         emit finished(trainer::length, trainer::errs, trainer::time);
    }
}
void trainer::onTimer()
{
    int mseconds = _timeLeft.msecsSinceStartOfDay() + QTime::currentTime().msecsSinceStartOfDay() - _lastStart.msecsSinceStartOfDay();
    ui->label_time->setText(QTime::fromMSecsSinceStartOfDay(mseconds).toString("mm:ss"));
    trainer::time = mseconds;
}

void trainer::on_Back_to_lesson_clicked()
{
    _timer.stop();
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning", "Are you sure?",
                                                              QMessageBox::Yes| QMessageBox::No);
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

void trainer::showResult(int n1, int n2, int n3)
{
    ui->startButton->setText("Try again!");
    result_window = new result();
    result_window->symbols = n1;
    result_window->errs = n2;
    result_window->time = n3 / 1000;
    result_window->setResult();
    result_window->show();
}
