#include "home.h"
#include "job_company.h"
#include "job_person.h"
#include "network_company.h"
#include "network_person.h"
#include "account.h"
#include "person.h"
#include "company.h"
#include "message.h"
#include "welcome.h"
#include "viwe_profile.h"
#include "serch.h"
#include "full_information.h"
#include "ui_home.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>  // برای نمایش لیست پست‌ها

static bool selectedLanguage;
bool home::isDarkMode = false;  // مقداردهی متغیر استاتیک در اینجا

home::home(const QString &Account_ID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
    , Account_ID(Account_ID)
    , postOffset(0)

{
    ui->setupUi(this);

    // تنظیم آیتم‌های ComboBox
    ui->comboBox_me->addItem(tr("..."));
    ui->comboBox_me->addItem(tr("ویرایش اطلاعات"));
    ui->comboBox_me->addItem(tr("خروج"));

    translateUi(welcome::selectedLanguage);
    setDarkMode(isDarkMode);

    // بارگذاری تاریخچه جستجو
    loadSearchHistory();

    // بارگذاری پست‌ها
    //loadPosts();
}

home::~home()
{
    delete ui;
}

void home::loadUsername() {
    ui->pushButton_me->setText(Account_ID);
}

void home::determineUserType() {

}


void home::loadPosts() {

}

void home::displayPosts(const QList<QString> &posts) {
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(posts);
    ui->listView->setModel(model);
}

void home::on_pushButton_more_clicked() {
    postOffset += 10;
    loadPosts();
}

void home::on_pushButton_ago_clicked() {
    if (postOffset >= 10) {
        postOffset -= 10;
        loadPosts();
    }
}

void home::loadSearchHistory() {
    QSqlDatabase db = QSqlDatabase::database();
    Person person;
    std::vector<std::string> history;
    if (person.loadFromDatabase(Account_ID.toStdString(), db)) {
        QStringList historyList;
        for (const auto &search : history) {
            historyList << QString::fromStdString(search);
        }
        displaySearchHistory(historyList);
    } else {
        qDebug() << "Error loading search history.";
    }
}

void home::updateSearchHistory(const QString &newSearch) {
    QSqlDatabase db = QSqlDatabase::database();
    Person person;
    if (person.updateSearchHistory(newSearch.toStdString(), db)) {
        loadSearchHistory();
    } else {
        qDebug() << "Error updating search history.";
    }
}

void home::displaySearchHistory(const QStringList &history) {
    ui->pushButton_serch_home_1->setText(history.value(0));
    ui->pushButton_serch_home_2->setText(history.value(1));
    ui->pushButton_serch_home_3->setText(history.value(2));
    ui->pushButton_serch_home_4->setText(history.value(3));
    ui->pushButton_serch_home_5->setText(history.value(4));
}

//رفتن به صفحات دیگر
void home::on_pushButton_serch_home_clicked() {
    QString searchText = ui->lineEdit_serch_home->text();
    if (!searchText.isEmpty()) {
        updateSearchHistory(searchText);
        serch *serchPage = new serch(Account_ID, searchText);
        serchPage->show();
    }
}

void home::on_pushButton_serch_home_1_clicked() {
    QString searchText = ui->pushButton_serch_home_1->text();
    if (!searchText.isEmpty()) {
        ui->lineEdit_serch_home->setText(searchText);
        serch *serchPage = new serch(Account_ID, searchText);
        serchPage->show();
    }
}

void home::on_pushButton_serch_home_2_clicked() {
    QString searchText = ui->pushButton_serch_home_2->text();
    if (!searchText.isEmpty()) {
        ui->lineEdit_serch_home->setText(searchText);
        serch *serchPage = new serch(Account_ID, searchText);
        serchPage->show();
    }
}

void home::on_pushButton_serch_home_3_clicked() {
    QString searchText = ui->pushButton_serch_home_3->text();
    if (!searchText.isEmpty()) {
        ui->lineEdit_serch_home->setText(searchText);
        serch *serchPage = new serch(Account_ID, searchText);
        serchPage->show();
    }
}

void home::on_pushButton_serch_home_4_clicked() {
    QString searchText = ui->pushButton_serch_home_4->text();
    if (!searchText.isEmpty()) {
        ui->lineEdit_serch_home->setText(searchText);
        serch *serchPage = new serch(Account_ID, searchText);
        serchPage->show();
    }
}

void home::on_pushButton_serch_home_5_clicked() {
    QString searchText = ui->pushButton_serch_home_5->text();
    if (!searchText.isEmpty()) {
        ui->lineEdit_serch_home->setText(searchText);
        serch *serchPage = new serch(Account_ID, searchText);
        serchPage->show();
    }
}

void home::on_pushButton_home_home_clicked()
{
    home *homePage = new home(Account_ID);
    homePage->show();
    this->hide();
}

void home::on_pushButton_job_home_clicked()
{
    if (isCompany) {
        job_company *jobPage = new job_company(Account_ID);
        jobPage->show();
    } else {
        job_person *jobPage = new job_person(Account_ID);
        jobPage->show();
    }
    this->hide();
}

void home::on_pushButton_network_home_clicked()
{
    if (isCompany) {
        network_company *network_companyPage = new network_company(Account_ID);
        network_companyPage->show();
    } else {
        network_person *network_personPage = new network_person(Account_ID);
        network_personPage->show();
    }
    this->hide();
}

void home::on_pushButton_message_home_clicked()
{
    message *messagePage = new message(Account_ID);
    messagePage->show();
    this->hide();
}

void home::on_comboBox_me_activated(int index)
{
    switch (index) {
    case 0:{
        viwe_profile *viwe_profilePage = new viwe_profile(Account_ID);
        viwe_profilePage->show();
        break;
    }
    case 1: {
        full_information *full_informationPage = new full_information(Account_ID);
        full_informationPage->show();
        this->hide();
        break;
    }
    case 2: {
        welcome *welcomePage = new welcome;
        welcomePage->show();
        this->hide();
        break;
    }
    }
}

//توابع و دکمه های زبان و تیره یا روشن
void home::on_pushButton_English_home_clicked()
{
    selectedLanguage = false;
    translateUi(selectedLanguage);
}

void home::on_pushButton_Persian_home_clicked()
{
    selectedLanguage = true;
    translateUi(selectedLanguage);
}

void home::setDarkMode(bool dark)
{
    isDarkMode = dark;
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
        ui->pushButton_dark_sun->setStyleSheet("border-image: url(:/new/prefix1/image/sun-dark.png);");
        ui->frame_HA_home->setStyleSheet("border-image: url(:/new/prefix1/image/HA-dark.png);");
        ui->widget->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget1->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget2->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget3->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->widget4->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->Widget5->setStyleSheet("background-color: rgb(255, 196, 54);");
    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");
        ui->pushButton_dark_sun->setStyleSheet("border-image: url(:/new/prefix1/image/moon-sun.png);");
        ui->frame_HA_home->setStyleSheet("border-image: url(:/new/prefix1/image/HA-sun.png);");
        ui->widget4->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget1->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget2->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->widget3->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->Widget5->setStyleSheet("background-color: rgb(252, 220, 116);");
    }
}

void home::on_pushButton_dark_sun_clicked()
{
    isDarkMode = !isDarkMode;
    setDarkMode(isDarkMode);
}

void home::translateUi(bool Language) {
    welcome::selectedLanguage = Language;
    if (Language) {
        ui->pushButton_serch_home->setText("جست و جو");
        ui->comboBox_me->setItemText(0, "نمایش اطلاعات");
        ui->comboBox_me->setItemText(1, "ویرایش اطلاعات");
        ui->comboBox_me->setItemText(2, "خروج");
        ui->pushButton_ago->setText("قبلی");
        ui->pushButton_more->setText("بیشتر");
        ui->pushButton_start_post->setText("پست بزار");

    } else {
        ui->pushButton_serch_home->setText("serch");
        ui->comboBox_me->setItemText(0, "viwe profile");
        ui->comboBox_me->setItemText(1, "Edit Info");
        ui->comboBox_me->setItemText(2, "Logout");
        ui->pushButton_ago->setText("ago");
        ui->pushButton_more->setText("more");
        ui->pushButton_start_post->setText("start post");
    }
}
