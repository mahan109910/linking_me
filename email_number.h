#ifndef EMAIL_NUMBER_H
#define EMAIL_NUMBER_H

#include <QMainWindow>

namespace Ui {
class email_number;
}

class email_number : public QMainWindow
{
    Q_OBJECT

public:
    explicit email_number(QWidget *parent = nullptr);
    ~email_number();

private slots:
    void on_pushButton_ok_email_clicked();

private:
    Ui::email_number *ui;
};

#endif // EMAIL_NUMBER_H
