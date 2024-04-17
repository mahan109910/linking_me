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

private slots:
    void on_pushButton_Persian_clicked();
    void on_pushButton_English_clicked();
    void on_pushButton_P_Register_clicked();
    void on_pushButton_P_LogIn_clicked();
    void on_pushButton_E_Register_clicked();
    void on_pushButton_E_LonIn_clicked();

private:
    Ui::welcome *ui;
    int selectedLanguage; // Store selected language (1 for Persian, 2 for English)
};

#endif // WELCOME_H
