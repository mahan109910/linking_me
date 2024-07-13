#include "viwe_profile.h"
#include "ui_viwe_profile.h"
#include "account.h"
#include "person.h"
#include "home.h"
#include "welcome.h"
#include "company.h"

static bool selectedLanguage ;
static bool isDarkMode;

viwe_profile::viwe_profile(const QString &myAccountID, const QString &selectedUserID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viwe_profile)
    , myAccountID(myAccountID)
    , selectedUserID(selectedUserID)
{
    ui->setupUi(this);

    setDarkMode(home::isDarkMode);
    translateUi(welcome::selectedLanguage);

    //نمایش اطلاعات
    QSqlDatabase db = QSqlDatabase::database();
     Account account("", "", "", ""); // مقداردهی اولیه با آرگومان‌های خالی
    if (account.loadFromDatabase(selectedUserID.toStdString(), db)){
        ui->pushButton_Account_ID->setText(QString::fromStdString(account.Account_ID));
        ui->pushButton_Email->setText(QString::fromStdString(account.Email));
        ui->pushButton_Phone_number->setText(QString::fromStdString(account.Phone_number));
        // بارگذاری عکس پروفایل
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromStdString(account.getProfilePicture()));
        ui->label->setPixmap(pixmap);
    }

    Person person;
    if (person.loadFromDatabase(selectedUserID.toStdString(), db)) {
        ui->pushButton_First_name->setText(QString::fromStdString(person.First_name));
        ui->pushButton_Last_name->setText(QString::fromStdString(person.Last_name));
    }

    // نمایش مهارت‌ها
    ui->listWidget_Skill->clear();
    for (const auto& skill : person.Skills) {
        ui->listWidget_Skill->addItem(QString::fromStdString(skill));
    }


    // Check if the person is associated with a company
    Company company;
    if (company.loadFromDatabase(selectedUserID.toStdString(), db)) {
        ui->pushButton_company->setText(QString::fromStdString(company.Name));
        ui->pushButton_company_code->setText(QString::number(company.Company_Code));

        // Display other company-related information as needed
    }else {
        ui->pushButton_company->setText("no");
        ui->pushButton_company_code->setText("no");
    }
}

viwe_profile::~viwe_profile()
{
    delete ui;
}

//رنگ و زبان
void viwe_profile::translateUi(bool Language) {
    selectedLanguage = Language;
    if (Language) {
        ui->pushButton_Account_ID_2->setText("نام کاربری");
        ui->pushButton_company_2->setText("نام شرکت");
        ui->pushButton_company_code_2->setText("کد شرکت");
        ui->pushButton_Email_2->setText("ایمیل");
        ui->pushButton_Last_name_2->setText("نام");
        ui->pushButton_First_name_2->setText("نام خانوادگی");
        ui->pushButton_Phone_number_2->setText("شماره همراه");
        ui->pushButton_Skill_2->setText("مهارت");

    } else {
        ui->pushButton_Account_ID_2->setText("Account");
        ui->pushButton_company_2->setText("company");
        ui->pushButton_company_code_2->setText("company code");
        ui->pushButton_Email_2->setText("Email");
        ui->pushButton_Last_name_2->setText("Last name");
        ui->pushButton_First_name_2->setText("First name");
        ui->pushButton_Phone_number_2->setText("Phone number");
        ui->pushButton_Skill_2->setText("Skill");

    }
}

void viwe_profile::setDarkMode(bool dark)
{
    isDarkMode = dark;
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");

    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");

    }
}
