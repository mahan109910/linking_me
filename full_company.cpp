#include "full_company.h"
#include "ui_full_company.h"
#include "full_information.h"
#include "welcome.h"
#include "home.h"
#include "company.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include "snowanimation.h"
#include <QGraphicsScene>
#include <QGraphicsView>

static bool isDarkMode;
static bool selectedLanguage;

Full_company::Full_company(const QString &username, QWidget *parent)
    : QWidget(parent), ui(new Ui::Full_company), m_username(username)
{
    ui->setupUi(this);

    // ایجاد QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene);
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/background.jpg"))); // تنظیم عکس پس‌زمینه از فایل منبع

    // ایجاد شیء برف
    SnowAnimation *snow = new SnowAnimation();
    scene->addItem(snow);

    // اضافه کردن QGraphicsView به پنجره‌ی اصلی
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(view);
    ui->gridWidget_full_company->setLayout(layout); // جایگزین کنید ui->centralWidget با نام مناسب برای ویجت اصلی شما.

    setDarkMode(home::isDarkMode);
    translateUi(welcome::selectedLanguage);
    loadCompanyData(m_username);
}


Full_company::~Full_company()
{
    delete ui;
}

void Full_company::loadCompanyData(const QString &accountId) {
    QSqlDatabase db = QSqlDatabase::database();
    Company company;
    if (company.loadFromDatabase(accountId.toStdString(), db)) {
        ui->lineEdit_name_company->setText(QString::fromStdString(company.Name));
        ui->lineEdit_code_company->setText(QString::number(company.Company_Code));
    } else {
        qDebug() << "Failed to load company data.";
    }
}

void Full_company::on_pushButton_ok_company_clicked() {
    animatePushButton();
    QString companyCode = ui->lineEdit_code_company->text();
    QString companyName = ui->lineEdit_name_company->text();

    if (companyCode.isEmpty() || companyName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", selectedLanguage == 1 ? "لطفاً هم کد شرکت و هم نام شرکت را وارد کنید." : "Please enter both company code and name.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();

    // Check for unique company name and code
    QSqlQuery uniqueCheckQuery(db);
    uniqueCheckQuery.prepare("SELECT COUNT(*) FROM Company WHERE (company_name = ? OR company_code = ?) AND Account_ID != ?");
    uniqueCheckQuery.addBindValue(companyName);
    uniqueCheckQuery.addBindValue(companyCode);
    uniqueCheckQuery.addBindValue(m_username);
    if (!uniqueCheckQuery.exec() || !uniqueCheckQuery.next()) {
        qDebug() << "Error checking for unique company name and code:" << uniqueCheckQuery.lastError();
        return;
    }

    int uniqueCount = uniqueCheckQuery.value(0).toInt();
    if (uniqueCount > 0) {
        QMessageBox::warning(this, "Input Error", selectedLanguage == 1 ? "نام یا کد شرکت تکراری است. لطفاً نام و کد دیگری انتخاب کنید." : "Company name or code is not unique. Please choose a different name and code.");
        return;
    }

    std::string companyCodeStr = companyCode.toStdString();
    std::string companyNameStr = companyName.toStdString();

    Company company(m_username.toStdString(), companyNameStr, std::stoi(companyCodeStr));

    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM Company WHERE Account_ID = ?");
    checkQuery.addBindValue(m_username);
    if (!checkQuery.exec() || !checkQuery.next()) {
        qDebug() << "Error checking for existing company:" << checkQuery.lastError();
        return;
    }

    int count = checkQuery.value(0).toInt();
    if (count > 0) {
        if (company.updateInDatabase(db)) {
            QMessageBox::information(this, "Success", selectedLanguage == 1 ? "اطلاعات شرکت با موفقیت به‌روزرسانی شد!" : "Company data updated successfully!");
        } else {
            QMessageBox::critical(this, "Error", selectedLanguage == 1 ? "خطا در به‌روزرسانی اطلاعات شرکت." : "Failed to update company data.");
        }
    } else {
        if (company.saveToDatabase(db)) {
            QMessageBox::information(this, "Success", selectedLanguage == 1 ? "اطلاعات شرکت با موفقیت ذخیره شد!" : "Company data saved successfully!");
        } else {
            QMessageBox::critical(this, "Error", selectedLanguage == 1 ? "خطا در ذخیره اطلاعات شرکت." : "Failed to save company data.");
        }
    }
}


void Full_company::on_pushButton_bake_company_clicked() {
    home *homePage = new home(m_username);
    homePage->show();
    this->hide();
}

void Full_company::setDarkMode(bool dark) {
    isDarkMode = dark;
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
        ui->gridWidget_full_company->setStyleSheet("border-image: url(:/new/prefix1/image/full_company_dark.png);");
        ui->lineEdit_code_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang5.png);");
        ui->lineEdit_name_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang5.png);");
        ui->pushButton_code_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang5.png);");
        ui->pushButton_name_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang5.png);");
        ui->pushButton_bake_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang5.png);");
        ui->pushButton_ok_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang5.png);");
    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");
        ui->gridWidget_full_company->setStyleSheet("border-image: url(:/new/prefix1/image/full_company_sun.png);");
        ui->lineEdit_code_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang4.png);");
        ui->lineEdit_name_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang4.png);");
        ui->pushButton_code_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang4.png);");
        ui->pushButton_name_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang4.png);");
        ui->pushButton_bake_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang4.png);");
        ui->pushButton_ok_company->setStyleSheet("border-image: url(:/new/prefix1/image/rang4.png);");
    }
}

void Full_company::translateUi(bool selectedLanguage) {
    welcome::selectedLanguage = selectedLanguage;
    if (selectedLanguage == true) {
        ui->pushButton_code_company->setText("کد شرکت");
        ui->pushButton_name_company->setText("نام شرکت");
        ui->pushButton_bake_company->setText("بازگشت");
        ui->pushButton_ok_company->setText("تایید");
    } else if (selectedLanguage == false) {
        ui->pushButton_code_company->setText("Company Code");
        ui->pushButton_name_company->setText("Company Name");
        ui->pushButton_bake_company->setText("Back");
        ui->pushButton_ok_company->setText("OK");
    }
}

void Full_company::animatePushButton() {
    QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton_ok_company, "geometry");
    animation->setDuration(500); // مدت زمان انیمیشن به میلی‌ثانیه
    animation->setStartValue(ui->pushButton_ok_company->geometry());
    animation->setEndValue(QRect(ui->pushButton_ok_company->x(), ui->pushButton_ok_company->y(), ui->pushButton_ok_company->width() + 10, ui->pushButton_ok_company->height() + 10));
    animation->setEasingCurve(QEasingCurve::OutBounce); // نوع انیمیشن
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

