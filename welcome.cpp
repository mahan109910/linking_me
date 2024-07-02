#include "welcome.h"
#include "./ui_welcome.h"
#include "login.h"
#include "signin.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>

// اول 0 هست و بعد با انتخاب زبان فارسی=1 و انگلیسی=2 میشود
int welcome::selectedLanguage = 0;

welcome::welcome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::welcome)
{
    ui->setupUi(this);
    ui->backgroundFrame->show();
    ui->pushButton_LogIn->hide();
    ui->pushButton_Register->hide();
    ui->backgroundFrame->setStyleSheet("image: url(:/new/prefix1/image/qt8.png);");}

welcome::~welcome()
{
    delete ui;
}
//انتخاب زبان فارسی و نمایش کلید های ثبت نام و ورود
void welcome::on_pushButton_Persian_clicked()
{
    selectedLanguage = 1;
    ui->backgroundFrame->setStyleSheet("image: url(:/new/prefix1/image/qt2.png);");
    setStyleSheet("background-color: rgb(252, 220, 116);");
    ui->pushButton_LogIn->show();
    ui->pushButton_Register->show();
    ui->pushButton_LogIn->setText("قبلا ثبت نام کردید وارد شوید");
    ui->pushButton_Register->setText("همین حالا ثبت نام کنید");

}
//انتخاب زبان انگلیسی و نمایش کلید های ثبت نام و ورود
void welcome::on_pushButton_English_clicked()
{
    selectedLanguage = 2;
    ui->backgroundFrame->setStyleSheet("image: url(:/new/prefix1/image/qt1.png);");
    setStyleSheet("background-color: rgb(252, 220, 116);");
    ui->pushButton_LogIn->show();
    ui->pushButton_Register->show();
    ui->pushButton_LogIn->setText("You have already registered, enter");
    ui->pushButton_Register->setText("register now");
}
//کلید ورود به صفحع ثبت نام
void welcome::on_pushButton_Register_clicked()
{
    signin *signinPage = new signin;
    signinPage->show();
    this->hide();
}
//کلید ورود به صفحه ورود
void welcome::on_pushButton_LogIn_clicked()
{
    LogIn *LogInPage = new LogIn;
    LogInPage->show();
    this->hide();
}
