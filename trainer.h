#ifndef TRAINER_H
#define TRAINER_H

#include  "result.h"
#include <QWidget>
#include <QKeyEvent>
#include <QEventLoop>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMediaPlayer>

namespace Ui {
class trainer;
}

class trainer : public QWidget
{
    Q_OBJECT

public:
    explicit trainer(QWidget *parent = 0);
    ~trainer();

    void keyPressEvent(QKeyEvent* ke);

    QString w;
    QString fileName;
    int errs;
    bool flag = false;
    int length;
    int time;

    QMediaPlayer * player = new QMediaPlayer();

signals:
    void show_lesson_window();
    void pressed();
    void finished(int, int, int);

private slots:
    void on_Back_to_lesson_clicked();
    void startClicked();
    void on_pauseButton_clicked();
    void onTimer();
    void showResult(int, int, int);

private:
    Ui::trainer *ui;
    result *result_window;

    QTimer _timer;
    QTime _timeLeft;
    QTime _lastStart;
};

#endif // TRAINER_H
