#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_show_safe_clicked();
    void on_pushButton_ok_log_clicked();
    void on_pushButton_Persian_log_clicked();
    void on_pushButton_English_log_clicked();
    void on_pushButton_menu_log_clicked();
    void translateUi(bool selectedLanguage);



private:
    Ui::login *ui;
    QFrame* safeFrames[4];
    int safeCode[4];
    QSqlDatabase db;  // اضافه کردن دیتابیس به عنوان عضو کلاس

    void generateSafeCode();
    void updateLanguageSettings();
    void updateTextColor(const QString &text);
    void setButtonStyle(QPushButton* button);
    void setSafeImage(QFrame* frame, int value);
};

#endif // LOGIN_H
