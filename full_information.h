#ifndef FULL_INFORMATION_H
#define FULL_INFORMATION_H

#include <QWidget>
#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include <QByteArray>

namespace Ui {
class full_information;
}

class full_information : public QWidget
{
    Q_OBJECT

public:
    explicit full_information(const QString &username, QWidget *parent = nullptr);
    ~full_information();

private slots:
    void on_pushButton_persian_clicked();
    void on_pushButton_english_clicked();
    void on_pushButton_home_clicked();
    void on_pushButton_dark_sun_clicked();
    void on_pushButton_select_photo_clicked();
    void on_pushButton_sing_company_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_skill_clicked();

private:
    Ui::full_information *ui;
    QString username;
    QSqlDatabase db;
    QStringList skillsList;
    QByteArray profilePicture;

    void loadUserData();
    bool saveUserData();
    void updateSkillsDisplay();
    void setDarkMode(bool dark);
};

#endif // FULL_INFORMATION_H
