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
    explicit email_number(QWidget *parent = nullptr); // افزودن constructor با پارامتر پیش‌فرض
    ~email_number(); // اضافه کردن destructor

private slots:
               // اینجا می‌توانید اسلات‌های خود را اضافه کنید

private:
    Ui::email_number *ui;
};

#endif // EMAIL_NUMBER_H
