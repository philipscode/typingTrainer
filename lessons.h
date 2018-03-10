#ifndef LESSONS_H
#define LESSONS_H

#include <QDialog>
#include <QString>
#include "trainer.h"

namespace Ui {
class lessons;
}

class lessons : public QDialog

{
    Q_OBJECT

public:
    explicit lessons(QWidget *parent = 0);
    ~lessons();

signals:
    void main_window();
    void file_name(QString f);

private slots:
    void on_Back_to_menu_clicked();

    void on_lesson_1_clicked();

    void on_lesson_2_clicked();

    void on_lesson_3_clicked();

    void on_lesson_4_clicked();

    void on_lesson_5_clicked();

    void start_lesson(QString s);

private:
    Ui::lessons *ui;
    trainer * trainer_window;
};

#endif // LESSONS_H
