#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class signin; }
QT_END_NAMESPACE

class signin : public QMainWindow
{
    Q_OBJECT

public:
    signin(QWidget *parent = nullptr);
    ~signin();

private slots:
    void on_pushButton_show_safe_signin_clicked();
    void on_pushButton_ok_signin_clicked();
    void on_pushButton_Persian_signin_clicked();
    void on_pushButton_English_signin_clicked();
    void on_pushButton_menu_signin_clicked();

private:
    Ui::signin *ui;
    QFrame* safeFrames[4];
    int safeCode[4];
    QSqlDatabase db;  // اضافه کردن دیتابیس به عنوان عضو کلاس

    void generateSafeCode();
    void updateLanguageSettings();
    void updateTextColor(const QString &text);
    void setButtonStyle(QPushButton* button);
    void setSafeImage(QFrame* frame, int value);
};

#endif // SIGNIN_H
