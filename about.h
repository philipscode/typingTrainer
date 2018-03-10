#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

signals:
    void main_window();

private slots:
    void on_GoBack_clicked();

private:
    Ui::about *ui;

};

#endif // ABOUT_H
