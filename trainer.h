#ifndef TRAINER_H
#define TRAINER_H

#include <QWidget>
#include <QKeyEvent>
#include <QEventLoop>
#include <QString>
#include <QEvent>

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

    void fileRead();

    QString w;
    QString fileName;
    int errs;
    bool flag = false;

signals:
    void show_lesson_window();
    void pressed();

private slots:
    void on_Back_to_lesson_clicked();
    void startClicked();

private:
    Ui::trainer *ui;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // TRAINER_H
