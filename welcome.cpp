#include "welcome.h"
#include "./ui_welcome.h"
#include "login.h"
#include "singin.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
//inchude database
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"


welcome::welcome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::welcome)
{
    ui->setupUi(this);
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("d:\\database_linking.db");
    database.open();

    // Initialize selectedLanguage to 0 (default)
    selectedLanguage = 0;

    ui->backgroundFrame->setStyleSheet("image: url(:/new/prefix1/image/qt8.png);");
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
    setStyleSheet("background-color: rgb(255, 196, 54);");
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
    setStyleSheet("background-color: rgb(255, 196, 54);");
    ui->backgroundFrame->show();
    ui->pushButton_P_LogIn->hide();
    ui->pushButton_P_Register->hide();
    ui->pushButton_E_LonIn->show();
    ui->pushButton_E_Register->show();
}

void welcome::on_pushButton_P_Register_clicked()
{
    singIn *w2 = new singIn;
    // Pass the selectedLanguage to singIn
    w2->setLanguage(selectedLanguage);
    w2->show();
}

void welcome::on_pushButton_P_LogIn_clicked()
{
    LogIn *wlog = new LogIn;
    wlog->show();
}

void welcome::on_pushButton_E_Register_clicked()
{
    singIn *w2 = new singIn;
    // Pass the selectedLanguage to singIn
    w2->setLanguage(selectedLanguage);
    w2->show();
}

void welcome::on_pushButton_E_LonIn_clicked()
{
    LogIn *wlog = new LogIn;
    wlog->show();
}
