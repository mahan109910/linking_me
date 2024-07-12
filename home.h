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
    void on_pushButton_more_clicked();
    void on_pushButton_ago_clicked();
    void on_pushButton_serch_home_clicked();
    void on_pushButton_serch_home_1_clicked();
    void on_pushButton_serch_home_2_clicked();
    void on_pushButton_serch_home_3_clicked();
    void on_pushButton_serch_home_4_clicked();
    void on_pushButton_serch_home_5_clicked();
    void loadUsername();

private:
    Ui::home *ui;
    QString Account_ID;
    bool isCompany;
    QSqlDatabase db;
    int postOffset;
    void loadPosts();
    void displayPosts(const QList<QString> &posts);
    void translateUi(bool Language);
    void setDarkMode(bool dark);
    void loadSearchHistory();
    void updateSearchHistory(const QString &newSearch);
    void displaySearchHistory(const QStringList &history);
    void determineUserType();

};

#endif // HOME_H
