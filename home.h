#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QString>

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_pushButton_English_home_clicked();
    void on_pushButton_Persian_home_clicked();
    void on_pushButton_home_home_clicked();
    void on_pushButton_job_home_clicked();
    void on_pushButton_network_home_clicked();
    void on_pushButton_message_home_clicked();
    void on_pushButton_dark_sun_clicked();
    void on_comboBox_me_activated(int index);

private:
    Ui::home *ui;
    bool isDarkMode;
    void setDarkMode(bool dark);
    QString getUserName(const QString &userID);  // اعلام تابع getUserName
    QString readUsernameFromFile();  // اعلام تابع readUsernameFromFile
};

#endif // HOME_H
