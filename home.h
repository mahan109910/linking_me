#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(const QString &Account_ID, QWidget *parent = nullptr);
    ~home();
    static bool isDarkMode;  // فقط اعلام متغیر استاتیک

private slots:
    void on_pushButton_English_home_clicked();
    void on_pushButton_Persian_home_clicked();
    void on_pushButton_home_home_clicked();
    void on_pushButton_job_home_clicked();
    void on_pushButton_network_home_clicked();
    void on_pushButton_message_home_clicked();
    void on_pushButton_dark_sun_clicked();
    void on_comboBox_me_activated(int index);
    void loadPosts();
    void on_pushButton_more_clicked();
    void on_pushButton_ago_clicked();
    void setDarkMode(bool dark);
    void translateUi(bool Language);
    void loadUsername();
    void displayPosts(const QList<QString> &posts);
    void determineUserType();

    void on_pushButton_serch_home_clicked();

private:
    Ui::home *ui;
    QString Account_ID;
    bool isCompany;
    QSqlDatabase db;
    int postOffset;

};

#endif // HOME_H
