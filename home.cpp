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
#include "ui_home.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>  // برای نمایش لیست پست‌ها

static int selectedLanguage = 0;

home::home(const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
    , isDarkMode(false)
    , username(username)
    , postOffset(0)
{
    ui->setupUi(this);
    setDarkMode(isDarkMode);

    // تنظیم دیتابیس و بارگذاری نام کاربری
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\sobooty\\Qt\\start-me\\sqlite\\me-test-1.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to connect to database!";
    } else {
        qDebug() << "Database connected successfully!";
        loadUsername();
        determineUserType();
    }

    // تنظیم آیتم‌های ComboBox
    ui->comboBox_me->addItem(tr("اطلاعات"));
    ui->comboBox_me->addItem(tr("ویرایش اطلاعات"));
    ui->comboBox_me->addItem(tr("خروج"));

    // بارگذاری پست‌ها
    loadPosts();
}

home::~home()
{
    delete ui;
}

void home::loadUsername() {
    ui->pushButton_me->setText(username);
}

void home::determineUserType() {
    QSqlQuery query(db);
    query.prepare("SELECT is_company FROM Users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.first()) {
        isCompany = query.value(0).toBool();
    } else {
        qDebug() << "Failed to determine user type:" << query.lastError();
    }
}

void home::on_pushButton_English_home_clicked()
{
    selectedLanguage = 2;
    translateUi();
}

void home::on_pushButton_Persian_home_clicked()
{
    selectedLanguage = 1;
    translateUi();
}

void home::translateUi() {
    if (selectedLanguage == 1) {
        ui->pushButton_serch_home->setText("جست و جو");
        ui->comboBox_me->setItemText(0, "اطلاعات");
        ui->comboBox_me->setItemText(1, "ویرایش اطلاعات");
        ui->comboBox_me->setItemText(2, "خروج");
    } else if (selectedLanguage == 2) {
        ui->pushButton_serch_home->setText("search");
        ui->comboBox_me->setItemText(0, "Info");
        ui->comboBox_me->setItemText(1, "Edit Info");
        ui->comboBox_me->setItemText(2, "Logout");
    }
}

void home::on_pushButton_home_home_clicked()
{
    home *homePage = new home(username);
    homePage->show();
    this->hide();
}

void home::on_pushButton_job_home_clicked()
{
    if (isCompany) {
        job_company *jobPage = new job_company(username);
        jobPage->show();
    } else {
        job_person *jobPage = new job_person(username);
        jobPage->show();
    }
    this->hide();
}

void home::on_pushButton_network_home_clicked()
{
    if (isCompany) {
        network_company *network_companyPage = new network_company(username);
        network_companyPage->show();
    } else {
        network_person *network_personPage = new network_person(username);
        network_personPage->show();
    }
    this->hide();
}

void home::on_pushButton_message_home_clicked()
{
    message *messagePage = new message(username);
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
        // رفتن به صفحه نمایش اطلاعات
        break;
    case 1:
        // رفتن به صفحه ویرایش اطلاعات
        break;
    case 2:
        welcome *welcomePage = new welcome;
        welcomePage->show();
        this->hide();
        break;
    }
}

void home::loadPosts() {
    QSqlQuery query(db);
    query.prepare("SELECT content FROM Posts ORDER BY priority LIMIT 10 OFFSET :offset");
    query.bindValue(":offset", postOffset);

    if (query.exec()) {
        QList<QString> posts;
        while (query.next()) {
            posts.append(query.value(0).toString());
        }
        displayPosts(posts);
    } else {
        qDebug() << "Failed to load posts:" << query.lastError();
    }
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
