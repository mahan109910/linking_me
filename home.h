#ifndef HOME_H
#define HOME_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class home; }
QT_END_NAMESPACE

class home : public QWidget
{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_pushButton_English_home_clicked();
    void on_pushButton_Persian_home_clicked();
    void on_pushButton_home_home_clicked();
    void on_pushButton_job_home_clicked();
    void on_pushButton_network_home_clicked();
    void on_pushButton_message_home_clicked();
    void on_pushButton_dark_sun_clicked();

private:
    Ui::home *ui;
    bool isDarkMode;  // متغیر وضعیت برای حالت تاریک
    void setDarkMode(bool dark);  // تابع برای تنظیم حالت تاریک یا روشن
};

#endif // HOME_H
