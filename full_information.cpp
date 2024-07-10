#include "full_information.h"
#include "ui_full_information.h"
#include "full_company.h"
#include "home.h"
#include "welcome.h"
#include "account.h"
#include "person.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPixmap>
#include <QBitmap>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include <sstream>
#include "iostream"

static int selectedLanguage = 0;
static bool isDarkMode = false;

full_information::full_information(const QString &username, QWidget *parent)
    : QWidget(parent), ui(new Ui::full_information), username(username)
{
    ui->setupUi(this);

    setDarkMode(home::isDarkMode);
    db = QSqlDatabase::database();
    loadUserData();

    welcome welcomeInstance; // ایجاد نمونه از کلاس welcome برای تنظیم زبان از ابتدا
    selectedLanguage = welcomeInstance.selectedLanguage;

    translateUi();
}

full_information::~full_information()
{
    delete ui;
}

void full_information::on_pushButton_persian_clicked()
{
    selectedLanguage = 1;
    translateUi();
}

void full_information::on_pushButton_english_clicked()
{
    selectedLanguage = 2;
    translateUi();
}

void full_information::translateUi() {
    if (selectedLanguage == 1) {
        ui->pushButton_home->setText("خانه");
        ui->pushButton_dark_sun->setText("");
        ui->pushButton_sing_company->setText("اگر شرکت هستید از این جا ثبت نام کنید");
    } else if (selectedLanguage == 2) {
        ui->pushButton_home->setText("Home");
        ui->pushButton_dark_sun->setText("");
        ui->pushButton_sing_company->setText("If you are a company, register here");
    }
}

void full_information::on_pushButton_home_clicked()
{
    home *homePage = new home(username);
    homePage->show();
    this->hide();
}

void full_information::on_pushButton_dark_sun_clicked()
{
    isDarkMode = !isDarkMode;
    setDarkMode(isDarkMode);
}

void full_information::on_pushButton_select_photo_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Photo"), "", tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QBitmap mask = pixmap.createMaskFromColor(Qt::transparent, Qt::MaskInColor);
        pixmap.setMask(mask);
        ui->label_photo->setPixmap(pixmap);

        QBuffer buffer(&profilePicture);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
    }
}

void full_information::on_pushButton_sing_company_clicked()
{
    Full_company *Full_companyPage = new Full_company(username);
    Full_companyPage->show();
    this->hide();
}

void full_information::on_pushButton_ok_clicked()
{
    // خواندن اطلاعات از ویجت‌ها
    QString firstName = ui->lineEdit_name->text();
    QString lastName = ui->lineEdit_last_name->text();
    QString email = ui->emailLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString password = ui->lineEdit_password->text();
    QString id = ui->lineEdit_id->text();
    //QString bio = ui->bioTextEdit->toPlainText();
    QByteArray profilePictureData = profilePicture;  // اینجا شما باید کدی بنویسید که عکس پروفایل را بخواند

    // تبدیل QString به std::string
    std::string firstNameStr = firstName.toStdString();
    std::string lastNameStr = lastName.toStdString();
    std::string emailStr = email.toStdString();
    std::string phoneStr = phone.toStdString();
    std::string passwordStr = password.toStdString();
    std::string idStr = id.toStdString();
    //std::string bioStr = bio.toStdString();
    std::string profilePictureStr = profilePictureData.toStdString();

    // ذخیره اطلاعات در دیتابیس با استفاده از کلاس‌ها

    // ذخیره اطلاعات در جدول Account
    Account account(idStr, phoneStr, emailStr, passwordStr/*, bioStr*/);
    account.setProfilePicture(profilePictureStr);

    QSqlDatabase db = QSqlDatabase::database();
    if (account.saveToDatabase(db)) {
        QMessageBox::information(this, "Success", "Account data saved successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save Account data.");
    }

    // ذخیره اطلاعات در جدول Person
    Person person(idStr, firstNameStr, lastNameStr);

    if (person.saveToDatabase(db)) {
        QMessageBox::information(this, "Success", "Person data saved successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save Person data.");
    }
}

void full_information::on_pushButton_skill_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->listWidget_skills->selectedItems();
    foreach (QListWidgetItem *item, selectedItems) {
        QString skill = item->text();
        if (!skillsList.contains(skill)) { // بررسی تکراری نبودن مهارت
            skillsList.append(skill);
        }
    }
    updateSkillsDisplay();
}

void full_information::updateSkillsDisplay()
{
    ui->listWidget_skills->clear();
    foreach (const QString &skill, skillsList) {
        QListWidgetItem *item = new QListWidgetItem(skill, ui->listWidget_skills);
        item->setSelected(true);  // Select item by default
    }
}

void full_information::loadUserData()
{
    QSqlDatabase db = QSqlDatabase::database();

    Account account("", "", "", ""); // مقداردهی اولیه با آرگومان‌های خالی
    if (account.loadFromDatabase(username.toStdString(), db)) {
        ui->lineEdit_id->setText(QString::fromStdString(account.Account_ID));
        ui->emailLineEdit->setText(QString::fromStdString(account.Email));
        ui->phoneLineEdit->setText(QString::fromStdString(account.Phone_number));
        ui->lineEdit_password->setText(QString::fromStdString(account.password));
        //ui->bioTextEdit->setText(QString::fromStdString(account.bio));

        // بارگذاری عکس پروفایل
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromStdString(account.getProfilePicture()));
        ui->label_photo->setPixmap(pixmap);
    } else {
        QMessageBox::critical(this, "Error", "Failed to load user data.");
    }

    Person person;
    if (person.loadFromDatabase(username.toStdString(), db)) {
        ui->lineEdit_name->setText(QString::fromStdString(person.First_name));
        ui->lineEdit_last_name->setText(QString::fromStdString(person.Last_name));
        /*QStringList skillList = QStringList::fromVector(QVector<QString>::fromStdVector(person.getSkills()));
        skillsList = skillList;*/
        updateSkillsDisplay();
    } else {
        QMessageBox::critical(this, "Error", "Failed to load person data.");
    }
}

void full_information::setDarkMode(bool dark)
{
    home::isDarkMode = dark;
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
        ui->pushButton_dark_sun->setStyleSheet("border-image: url(:/new/prefix1/image/sun-dark.png);");
        ui->label_photo->setStyleSheet("background-color: rgb(9, 0, 137)");
        ui->horizontalFrame_4->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->horizontalWidget_3->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->groupBox_2->setStyleSheet("background-color: rgb(255, 196, 54);");
    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");
        ui->pushButton_dark_sun->setStyleSheet("border-image: url(:/new/prefix1/image/moon-sun.png);");
        ui->label_photo->setStyleSheet("background-color: rgb(145, 206, 255);");
        ui->horizontalFrame_4->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->horizontalWidget_3->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->groupBox_2->setStyleSheet("background-color: rgb(252, 220, 116);");
    }
}
