#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class welcome; }
QT_END_NAMESPACE


class welcome : public QMainWindow
{
    Q_OBJECT

public:
    welcome(QWidget *parent = nullptr);
    ~welcome();
    static bool selectedLanguage;

private slots:
    void on_pushButton_Persian_clicked();
    void on_pushButton_English_clicked();
    void on_pushButton_Register_clicked();
    void on_pushButton_LogIn_clicked();
    void translateUi(bool selectedLanguage);

private:
    Ui::welcome *ui;
};

#endif // WELCOME_H
