#ifndef RESULT_H
#define RESULT_H

#include <QDialog>

namespace Ui {
class result;
}

class result : public QDialog
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = 0);
    ~result();

    int symbols;
    int errs;
    double time;
    double speed;

    void setResult();

private slots:
    void on_backButton_clicked();

private:
    Ui::result *ui;
};

#endif // RESULT_H
