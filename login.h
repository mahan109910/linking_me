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

    void setLanguage(int language);

private slots:
    void on_pushButton_show_safe_l_clicked();
    void on_pushButton_ok_log_clicked();

private:
    Ui::LogIn *ui;
    int selectedLanguage; // Store selected language (1 for Persian, 2 for English)
    QFrame* safeFrames_l[4]; // Array of pointers to safe frames
    int safeCode_l[4]; // Array to store generated safe code

    void setSafeImage(QFrame* frame, int value);
    void generateSafeCode(); // Declaration of generateSafeCode() function
};

#endif // LOGIN_H
