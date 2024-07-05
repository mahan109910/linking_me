#include "login.h"
#include "ui_login.h"
#include "welcome.h"
#include "signin.h"
#include "managers.h"
#include "home.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include <QTableView>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFile>
#include <QTextStream>

static int selectedLanguage = 0;

LogIn::LogIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    // تنظیمات مربوط به دیتابیس
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:\\sobooty\\Qt\\start-me\\sqlite\\me-test-1.db");

    if (!database.open()) {
        qDebug() << "Error: Unable to connect to database!";
    } else {
        qDebug() << "Database connected successfully!";
    }

    welcome welcomeInstance;
    selectedLanguage = welcomeInstance.selectedLanguage;

    if (selectedLanguage == 1) {
        ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_log_p.png);");
        ui->pushButton_menu_log->setText("صفحه اصلی");
        ui->pushButton_show_safe->setText("نمایش عدد");
        ui->pushButton_ok_log->setText("تایید");
    } else if (selectedLanguage == 2) {
        ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_log_e.png);");
        ui->pushButton_menu_log->setText("menu");
        ui->pushButton_show_safe->setText("show number");
        ui->pushButton_ok_log->setText("ok");
    }

    // تنظیم استایل ورودی‌ها
    QString lineEditStyle = "QLineEdit { background-color: white; color: black; }";
    ui->lineEdit_log_safe->setStyleSheet(lineEditStyle);
    ui->lineEdit_log_name->setStyleSheet(lineEditStyle);
    ui->lineEdit_log_Password->setStyleSheet(lineEditStyle);
    ui->lineEdit_log_safe->setStyleSheet(lineEditStyle);

    ui->lineEdit_log_safe->setValidator(new QIntValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_log_name->setValidator(nameValidator);
}

LogIn::~LogIn()
{
    delete ui;
}

// تابع برای ذخیره نام کاربری در فایل
void LogIn::saveUsernameToFile(const QString &username)
{
    QString fileName = "saved_username.txt";  // نام فایل برای ذخیره نام کاربری

    // باز کردن یک فایل برای نوشتن
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << username;  // نوشتن نام کاربری در فایل
        file.close();
        qDebug() << "Username saved to file.";
    } else {
        qDebug() << "Error: Unable to open file for writing.";
    }
}

// تابع برای تولید تصویر کد ایمنی
void LogIn::setSafeImage(QFrame* frame, int value) {
    QString imagePath = QString(":/new/prefix1/image/%1.png").arg(value);
    frame->setStyleSheet("image: url(" + imagePath + ");");
}

// تابع برای تولید کد ایمنی
void LogIn::generateSafeCode() {
    for (int i = 0; i < 4; ++i) {
        safeCode_l[i] = QRandomGenerator::global()->bounded(10);
        setSafeImage(safeFrames_l[i], safeCode_l[i]);
    }
}

// دکمه نمایش کد ایمنی
void LogIn::on_pushButton_show_safe_clicked()
{
    ui->lineEdit_log_Password->setValidator(new QIntValidator());
    safeFrames_l[0] = ui->frame_safe_1l;
    safeFrames_l[1] = ui->frame_safe_2l;
    safeFrames_l[2] = ui->frame_safe_3l;
    safeFrames_l[3] = ui->frame_safe_4l;
    generateSafeCode();
}

// دکمه تایید ورود
void LogIn::on_pushButton_ok_log_clicked() {
    int key_l = ui->lineEdit_log_safe->text().toInt();

    int enteredCode_l[4];
    enteredCode_l[0] = key_l / 1000;
    enteredCode_l[1] = (key_l / 100) % 10;
    enteredCode_l[2] = (key_l / 10) % 10;
    enteredCode_l[3] = key_l % 10;

    bool isValid = true;
    for (int i = 0; i < 4; ++i) {
        if (enteredCode_l[i] != safeCode_l[i]) {
            isValid = false;
            break;
        }
    }

    QString name = ui->lineEdit_log_name->text();
    QString password = ui->lineEdit_log_Password->text();

    if (isValid) {
        if (name.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "خطا", "لطفا تمام فیلدها را پر کنید.");
        } else {
            QSqlQuery query;
            query.prepare("SELECT * FROM Account WHERE Account_ID = :name AND password = :password");
            query.bindValue(":name", name);
            query.bindValue(":password", password.toInt());
            query.exec();

            if (query.next()) {
                // ذخیره نام کاربری در فایل
                saveUsernameToFile(name);

                home *homePage = new home;
                homePage->show();
                this->hide();
            } else {
                QMessageBox::warning(this, "ورود نا معتبر", "نام کاربری یا رمز عبور اشتباه است.");
            }
        }
    } else {
        QMessageBox::warning(this, "کد نادرست", "کد وارد شده نادرست است.");
    }
}

// دکمه تغییر به زبان فارسی
void LogIn::on_pushButton_Persian_log_clicked()
{
    ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_log_p.png);");
    ui->pushButton_menu_log->setText("صفحه اصلی");
    ui->pushButton_show_safe->setText("نمایش عدد");
    ui->pushButton_ok_log->setText("تایید");
}

// دکمه تغییر به زبان انگلیسی
void LogIn::on_pushButton_English_log_clicked()
{
    ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_log_e.png);");
    ui->pushButton_menu_log->setText("menu");
    ui->pushButton_show_safe->setText("show number");
    ui->pushButton_ok_log->setText("ok");
}

// دکمه بازگشت به صفحه خوشامدگویی
void LogIn::on_pushButton_menu_log_clicked()
{
    welcome *welcomePage = new welcome;
    welcomePage->show();
    this->hide();
}
