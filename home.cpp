#include "home.h"
#include "jobui.h"
#include "network.h"
#include "message.h"
#include "welcome.h"
#include "ui_home.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>

static int selectedLanguage = 0;

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
    , isDarkMode(false)
{
    ui->setupUi(this);
    setDarkMode(isDarkMode);

    // خواندن نام کاربری از فایل
    QString savedUsername = readUsernameFromFile();
    ui->pushButton_me->setText(savedUsername);

    ui->comboBox_me->addItem("اطلاعات");
    ui->comboBox_me->addItem("ویرایش اطلاعات");
    ui->comboBox_me->addItem("خروج");
}

home::~home()
{
    delete ui;
}

void home::on_pushButton_English_home_clicked()
{
    ui->pushButton_serch_home->setText("search");
}

void home::on_pushButton_Persian_home_clicked()
{
    ui->pushButton_serch_home->setText("جست و جو");
}

void home::on_pushButton_home_home_clicked()
{
    home *homePage = new home;
    homePage->show();
    this->hide();
}

void home::on_pushButton_job_home_clicked()
{
    /*jobui *jobuiPage = new jobui;
    jobuiPage->show();
    this->hide();*/
}

void home::on_pushButton_network_home_clicked()
{
    network *networkPage = new network;
    networkPage->show();
    this->hide();
}

void home::on_pushButton_message_home_clicked()
{
    message *messagePage = new message;
    messagePage->show();
    this->hide();
}

void home::setDarkMode(bool dark)
{
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
        ui->pushButton_dark_sun->setStyleSheet("background-image: url(:/new/prefix1/image/sun-daek.png);");
        ui->frame_HA_home->setStyleSheet("border-image: url(:/new/prefix1/image/HA-dark.png);");
        ui->pushButton_job_home->setStyleSheet("border-image: url(:/new/prefix1/image/job-dark.png); color: rgb(255, 255, 255);");
        ui->pushButton_network_home->setStyleSheet("border-image: url(:/new/prefix1/image/network-dark.png); color: rgb(255, 255, 255);");
        ui->pushButton_message_home->setStyleSheet("border-image: url(:/new/prefix1/image/message-dark.png); color: rgb(255, 255, 255);");
        ui->frame->setStyleSheet("background-color: rgb(9, 0, 137");
        ui->lineEdit_serch_home->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
        ui->widget->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget1->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget2->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget3->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->verticalWidget_3->setStyleSheet("background-color: rgb(255, 196, 54);");
    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");
        ui->pushButton_dark_sun->setStyleSheet("background-image: url(:/new/prefix1/image/moon-sun.png);");
        ui->frame_HA_home->setStyleSheet("border-image: url(:/new/prefix1/image/HA-sun.png);");
        ui->pushButton_job_home->setStyleSheet("border-image: url(:/new/prefix1/image/job-sun.png);");
        ui->pushButton_network_home->setStyleSheet("border-image: url(:/new/prefix1/image/network-sun.png);");
        ui->pushButton_message_home->setStyleSheet("border-image: url(:/new/prefix1/image/message-sun.png);");
        ui->frame->setStyleSheet("background-color: rgb(145, 206, 255);");
        ui->lineEdit_serch_home->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);");
        ui->widget->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget1->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget2->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget3->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->verticalWidget_3->setStyleSheet("background-color: rgb(252, 220, 116);");
    }
}

void home::on_pushButton_dark_sun_clicked()
{
    isDarkMode = !isDarkMode;
    setDarkMode(isDarkMode);
}

void home::on_comboBox_me_activated(int index)
{
    switch (index) {
    case 0:
        // کد مربوط به گزینه 0
        break;
    case 1:
        // کد مربوط به گزینه 1
        break;
    case 2:
        welcome *welcomePage = new welcome;
        welcomePage->show();
        this->hide();
        break;
    }
}

QString home::readUsernameFromFile() {
    QString fileName = "saved_username.txt";
    QString username;

    // باز کردن فایل برای خواندن
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        username = in.readLine();  // خواندن نام کاربری از فایل
        file.close();
        qDebug() << "Username read from file: " << username;
    } else {
        qDebug() << "Error: Unable to open file for reading.";
    }

    return username;
}
