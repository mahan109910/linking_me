#include "home.h"
#include "job.h"
#include "network.h"
#include "message.h"
#include "ui_home.h"

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
    , isDarkMode(false)  // مقداردهی اولیه به حالت روشن
{
    ui->setupUi(this);
    setDarkMode(isDarkMode);  // تنظیم حالت اولیه
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
    job *jobPage = new job;
    jobPage->show();
    this->hide();
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
        // تنظیم حالت تاریک
        this->setStyleSheet("background-color: rgb(45, 45, 45); color: rgb(255, 255, 255);");
        ui->pushButton_dark_sun->setText("Sun Mode");
        ui->pushButton_job_home->setStyleSheet("border-image: url(:/new/prefix1/image/job-dark.png); color: rgb(255, 255, 255);");
        ui->pushButton_network_home->setStyleSheet("border-image: url(:/new/prefix1/image/network-dark.png); color: rgb(255, 255, 255);");
        ui->pushButton_message_home->setStyleSheet("border-image: url(:/new/prefix1/image/message-dark.png); color: rgb(255, 255, 255);");
        ui->progressBar_information->setStyleSheet("background-color: rgb(0, 96, 202); selection-background-color: rgb(145, 206, 255); color: rgb(255, 255, 255);");
        ui->lineEdit_serch_home->setStyleSheet("background-color: rgb(0, 96, 202); color: rgb(255, 255, 255);");
    } else {
        // تنظیم حالت روشن
        this->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);");
        ui->pushButton_dark_sun->setText("Dark Mode");
        ui->pushButton_job_home->setStyleSheet("border-image: url(:/new/prefix1/image/job-light.png); color: rgb(0, 0, 0);");
        ui->pushButton_network_home->setStyleSheet("border-image: url(:/new/prefix1/image/network-light.png); color: rgb(0, 0, 0);");
        ui->pushButton_message_home->setStyleSheet("border-image: url(:/new/prefix1/image/message-light.png); color: rgb(0, 0, 0);");
        ui->progressBar_information->setStyleSheet("background-color: rgb(255, 255, 255); selection-background-color: rgb(0, 0, 0); color: rgb(0, 0, 0);");
        ui->lineEdit_serch_home->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);");
    }
}

void home::on_pushButton_dark_sun_clicked()
{
    isDarkMode = !isDarkMode;
    setDarkMode(isDarkMode);
}
