#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class singIn; }
QT_END_NAMESPACE

class singIn : public QMainWindow
{
    Q_OBJECT

public:
    singIn(QWidget *parent = nullptr);
    ~singIn();

    void setLanguage(int language);

private slots:
    void on_pushButton_show_safe_clicked();
    void on_pushButton_ok_sing_clicked();

private:
    Ui::singIn *ui;
    int selectedLanguage; // Store selected language (1 for Persian, 2 for English)
    QFrame* safeFrames[4]; // Array of pointers to safe frames
    int safeCode[4]; // Array to store generated safe code

    void setSafeImage(QFrame* frame, int value);
    void generateSafeCode(); // Declaration of generateSafeCode() function
};

#endif // SIGNIN_H
