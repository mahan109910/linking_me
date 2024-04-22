#include "welcome.h"
#include "./ui_welcome.h"
#include "login.h"
#include "signin.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>

// Initialize selectedLanguage to 0 (default)
int welcome::selectedLanguage = 0;

welcome::welcome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::welcome)
{
    ui->setupUi(this);
    ui->pushButton_E_LonIn->hide();
    ui->pushButton_E_Register->hide();
    ui->pushButton_P_LogIn->hide();
    ui->pushButton_P_Register->hide();
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_Persian_clicked()
{
    selectedLanguage = 1;
    ui->backgroundFrame->setStyleSheet("image: url(:/new/prefix1/image/qt2.png);");
    setStyleSheet("background-color: rgb(252, 220, 116);");
    ui->backgroundFrame->show();
    ui->pushButton_P_LogIn->show();
    ui->pushButton_P_Register->show();
    ui->pushButton_E_LonIn->hide();
    ui->pushButton_E_Register->hide();
}

void welcome::on_pushButton_English_clicked()
{
    selectedLanguage = 2;
    ui->backgroundFrame->setStyleSheet("image: url(:/new/prefix1/image/qt1.png);");
    setStyleSheet("background-color: rgb(252, 220, 116);");
    ui->backgroundFrame->show();
    ui->pushButton_P_LogIn->hide();
    ui->pushButton_P_Register->hide();
    ui->pushButton_E_LonIn->show();
    ui->pushButton_E_Register->show();
}

void welcome::on_pushButton_P_Register_clicked()
{
    singIn *singInPage = new singIn;
    singInPage->setLanguage(selectedLanguage);
    singInPage->show();
}

void welcome::on_pushButton_P_LogIn_clicked()
{
    LogIn *LogInPage = new LogIn;
    LogInPage->setLanguage(selectedLanguage);
    LogInPage->show();
}

void welcome::on_pushButton_E_Register_clicked()
{
    singIn *singInPage = new singIn;
    singInPage->setLanguage(selectedLanguage);
    singInPage->show();
}

void welcome::on_pushButton_E_LonIn_clicked()
{
    LogIn *LogInPage = new LogIn;
    LogInPage->setLanguage(selectedLanguage);
    LogInPage->show();
}
