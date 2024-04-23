#ifndef signin_H
#define signin_H

#include <QMainWindow>
#include <QFrame>

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
    void on_pushButton_ok_signin_clicked();

    void on_pushButton_show_safe_signin_clicked();

    void on_pushButton_show_safe_signin_2_clicked();

private:
    Ui::signin *ui;
    QFrame* safeFrames[4]; // Array of pointers to safe frames
    int safeCode[4]; // Array to store generated safe code

    void setSafeImage(QFrame* frame, int value);
    void generateSafeCode(); // Declaration of generateSafeCode() function
};

#endif // signin_H
