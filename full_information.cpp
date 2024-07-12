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

static bool selectedLanguage;
static bool isDarkMode;

full_information::full_information(const QString &username, QWidget *parent)
    : QWidget(parent), ui(new Ui::full_information), username(username) {
    ui->setupUi(this);

    db = QSqlDatabase::database();
    loadUserData();

    setDarkMode(home::isDarkMode);
    translateUi(welcome::selectedLanguage);
}

full_information::~full_information() {
    delete ui;
}

void full_information::on_pushButton_select_photo_clicked() {
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

void full_information::on_pushButton_ok_clicked() {
    // خواندن اطلاعات از ویجت‌ها
    QString firstName = ui->lineEdit_name->text();
    QString lastName = ui->lineEdit_last_name->text();
    QString email = ui->emailLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString password = ui->lineEdit_password->text();
    //QString bio = ui->bioTextEdit->toPlainText();
    QByteArray profilePictureData = profilePicture;

    // تبدیل QString به std::string
    std::string firstNameStr = firstName.toStdString();
    std::string lastNameStr = lastName.toStdString();
    std::string emailStr = email.toStdString();
    std::string phoneStr = phone.toStdString();
    std::string passwordStr = password.toStdString();
    //std::string bioStr = bio.toStdString();
    std::string profilePictureStr = profilePictureData.toStdString();

    // ذخیره اطلاعات در دیتابیس با استفاده از کلاس‌ها

    // ذخیره اطلاعات در جدول Account
    Account account(username.toStdString(), phoneStr, emailStr, passwordStr/*, bioStr*/);
    account.setProfilePicture(profilePictureStr);

    QSqlDatabase db = QSqlDatabase::database();
    if (account.saveToDatabase(db)) {
        QMessageBox::information(this, "Success", "Account data saved successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save Account data.");
    }

    // ذخیره اطلاعات در جدول Person
    Person person(username.toStdString(), firstNameStr, lastNameStr);
    std::vector<std::string> skills;
    for (const QString &skill : skillsList) {
        skills.push_back(skill.toStdString());
    }
    person.setSkills(skills);

    if (person.saveToDatabase(db)) {
        QMessageBox::information(this, "Success", "Person data saved successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save Person data.");
    }
}

void full_information::on_pushButton_skill_clicked() {
    QList<QListWidgetItem*> selectedItems = ui->listWidget_available_skills->selectedItems();
    foreach (QListWidgetItem *item, selectedItems) {
        QString skill = item->text();
        if (!skillsList.contains(skill)) { // بررسی تکراری نبودن مهارت
            skillsList.append(skill);
        }
    }
    updateSkillsDisplay();
}

void full_information::updateSkillsDisplay() {
    ui->listWidget_skills->clear();
    foreach (const QString &skill, skillsList) {
        QListWidgetItem *item = new QListWidgetItem(skill, ui->listWidget_skills);
        item->setSelected(true);  // Select item by default
    }
}

void full_information::loadUserData() {
    QSqlDatabase db = QSqlDatabase::database();

    Account account("", "", "", ""/*, ""*/); // مقداردهی اولیه با آرگومان‌های خالی
    if (account.loadFromDatabase(username.toStdString(), db)) {
        ui->pushButton_id_2->setText(QString::fromStdString(account.Account_ID));
        ui->emailLineEdit->setText(QString::fromStdString(account.Email));
        ui->phoneLineEdit->setText(QString::fromStdString(account.Phone_number));
        ui->lineEdit_password->setText(QString::fromStdString(account.password));
        //ui->bioTextEdit->setText(QString::fromStdString(account.Bio));

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
        QStringList skillList;
        for (const auto &skill : person.getSkills()) {
            skillList.append(QString::fromStdString(skill));
        }
        skillsList = skillList;
        updateSkillsDisplay();
    } else {
        QMessageBox::critical(this, "Error", "Failed to load person data.");
    }
}

void full_information::on_pushButton_remove_skill_clicked() {
    QList<QListWidgetItem*> selectedItems = ui->listWidget_skills->selectedItems();
    foreach (QListWidgetItem *item, selectedItems) {
        QString skill = item->text();
        skillsList.removeAll(skill);
    }
    updateSkillsDisplay();
}

//رفتن به صفحات بعد
void full_information::on_pushButton_sing_company_clicked()
{
    Full_company *Full_companyPage = new Full_company(username);
    Full_companyPage->show();
    this->hide();
}

void full_information::on_pushButton_home_clicked()
{
    home *homePage = new home(username);
    homePage->show();
    this->hide();
}

//توابع و دکمه های تغییر زبان و تیره یا روشن
void full_information::on_pushButton_persian_clicked()
{
    selectedLanguage = true;
    translateUi(selectedLanguage);
}

void full_information::on_pushButton_english_clicked()
{
    selectedLanguage = false;
    translateUi(selectedLanguage);
}

void full_information::on_pushButton_dark_sun_clicked()
{
    isDarkMode = !isDarkMode;
    setDarkMode(isDarkMode);
}

void full_information::translateUi(bool Language) {
    welcome::selectedLanguage = Language;
    if (Language) {
        ui->pushButton_home->setText("خانه");
        ui->pushButton_dark_sun->setText("");
        ui->pushButton_sing_company->setText("اگر شرکت هستید از این جا ثبت نام کنید");
        ui->emailLineEdit->setPlaceholderText("ایمیل");
        ui->lineEdit_password->setPlaceholderText("رمز عبور");
        ui->lineEdit_name->setPlaceholderText("نام");
        ui->lineEdit_last_name->setPlaceholderText("نام خانوادگی");
        ui->phoneLineEdit->setPlaceholderText("شماره تماس");
        ui->pushButton_skill->setText("مهارت");
        ui->pushButton_remove_skill->setText("حذف مهارت");
        ui->pushButton_select_photo->setText("انتخاب عکس");
        ui->pushButton_ok->setText("تأیید");
    } else {
        ui->pushButton_home->setText("Home");
        ui->pushButton_dark_sun->setText("");
        ui->pushButton_sing_company->setText("If you are a company, register here");
        ui->emailLineEdit->setPlaceholderText("Email");
        ui->lineEdit_password->setPlaceholderText("Password");
        ui->lineEdit_name->setPlaceholderText("First Name");
        ui->lineEdit_last_name->setPlaceholderText("Last Name");
        ui->phoneLineEdit->setPlaceholderText("Phone");
        ui->pushButton_skill->setText("Skill");
        ui->pushButton_remove_skill->setText("Remove Skill");
        ui->pushButton_select_photo->setText("Select Photo");
        ui->pushButton_ok->setText("OK");
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
