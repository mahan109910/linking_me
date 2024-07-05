#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class LogIn; }
QT_END_NAMESPACE

class LogIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_pushButton_show_safe_clicked();
    void on_pushButton_ok_log_clicked();
    void on_pushButton_Persian_log_clicked();
    void on_pushButton_English_log_clicked();
    void on_pushButton_menu_log_clicked();
    void saveUsernameToFile(const QString &username);

private:
    Ui::LogIn *ui;
    QFrame* safeFrames_l[4]; // Array of pointers to safe frames
    int safeCode_l[4]; // Array to store generated safe code

    void setSafeImage(QFrame* frame, int value);
    void generateSafeCode(); // Declaration of generateSafeCode() function
};

#endif // LOGIN_H
