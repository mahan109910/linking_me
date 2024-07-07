#include "login.h"
#include "ui_login.h"
#include "welcome.h"
#include "home.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

static int selectedLanguage = 0;

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    // تنظیمات مربوط به دیتابیس
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\sobooty\\Qt\\start-me\\sqlite\\me-test-1.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to connect to database!";
    } else {
        qDebug() << "Database connected successfully!";
    }

    welcome welcomeInstance; // ایجاد نمونه از کلاس welcome برای تنظیم زبان از ابتدا
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

    // تنظیم رنگ متن و پس‌زمینه برای lineEdit ها
    QString lineEditStyle = "QLineEdit { background-color: white; color: black; }";
    ui->lineEdit_log_safe->setStyleSheet(lineEditStyle);
    ui->lineEdit_log_name->setStyleSheet(lineEditStyle);
    ui->lineEdit_log_Password->setStyleSheet(lineEditStyle);

    ui->lineEdit_log_safe->setValidator(new QIntValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_log_name->setValidator(nameValidator);
}

login::~login()
{
    delete ui;
}

// تنظیم تصاویر کد امنیتی با توجه به عدد تصادفی
void login::setSafeImage(QFrame* frame, int value) {
    QString imagePath = QString(":/new/prefix1/image/%1.png").arg(value);
    frame->setStyleSheet("image: url(" + imagePath + ");");
}

void login::generateSafeCode() {
    for (int i = 0; i < 4; ++i) {
        safeCode[i] = QRandomGenerator::global()->bounded(10);
        setSafeImage(safeFrames[i], safeCode[i]);
    }
}

void login::on_pushButton_show_safe_clicked()
{
    safeFrames[0] = ui->frame_safe_1l;
    safeFrames[1] = ui->frame_safe_2l;
    safeFrames[2] = ui->frame_safe_3l;
    safeFrames[3] = ui->frame_safe_4l;
    generateSafeCode();
}

// بررسی درستی عدد با عددی که کاربر وارد می‌کند
void login::on_pushButton_ok_log_clicked()
{
    int key = ui->lineEdit_log_safe->text().toInt();
    int enteredCode[4];
    enteredCode[0] = key / 1000;
    enteredCode[1] = (key / 100) % 10;
    enteredCode[2] = (key / 10) % 10;
    enteredCode[3] = key % 10;

    bool isValid = true;
    for (int i = 0; i < 4; ++i) {
        if (enteredCode[i] != safeCode[i]) {
            isValid = false;
            break;
        }
    }

    QString username = ui->lineEdit_log_name->text();
    QString Password = ui->lineEdit_log_Password->text();

    if (isValid) {
        if (username.isEmpty() || Password.isEmpty()) {
            if (selectedLanguage == 1) {
                QMessageBox::warning(this, "خطا", "لطفا تمام فیلدها را پر کنید.");
            } else if (selectedLanguage == 2) {
                QMessageBox::warning(this, "Error", "Please fill in all fields.");
            }
        } else {
            QSqlQuery query(db);
            query.prepare("SELECT password FROM Account WHERE Account_ID = :name");
            query.bindValue(":name", username);
            query.exec();

            if (query.first()) {
                int storedPassword = query.value(0).toInt();
                if (Password.toInt() == storedPassword) {
                    if (selectedLanguage == 1) {
                        QMessageBox::information(this, "موفقیت", "ورود با موفقیت انجام شد.");
                    } else if (selectedLanguage == 2) {
                        QMessageBox::information(this, "Success", "Login successful.");
                    }
                    home *homePage = new home(username);
                    homePage->show();
                    this->hide();

                } else {
                    if (selectedLanguage == 1) {
                        QMessageBox::warning(this, "خطا", "رمز عبور نادرست است.");
                    } else if (selectedLanguage == 2) {
                        QMessageBox::warning(this, "Error", "Incorrect password.");
                    }
                }
            } else {
                if (selectedLanguage == 1) {
                    QMessageBox::warning(this, "خطا", "نام کاربری وجود ندارد.");
                } else if (selectedLanguage == 2) {
                    QMessageBox::warning(this, "Error", "Username does not exist.");
                }
            }
        }
    } else {
        if (selectedLanguage == 1) {
            QMessageBox::warning(this, "کد نادرست", "کد وارد شده نادرست است.");
        } else if (selectedLanguage == 2) {
            QMessageBox::warning(this, "Error", "Invalid code.");
        }
    }
}

// انتخاب زبان فارسی
void login::on_pushButton_Persian_log_clicked()
{
    selectedLanguage = 1;
    ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_log_p.png);");
    ui->pushButton_menu_log->setText("صفحه اصلی");
    ui->pushButton_show_safe->setText("نمایش عدد");
    ui->pushButton_ok_log->setText("تایید");
}

// انتخاب زبان انگلیسی
void login::on_pushButton_English_log_clicked()
{
    selectedLanguage = 2;
    ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_log_e.png);");
    ui->pushButton_menu_log->setText("menu");
    ui->pushButton_show_safe->setText("show number");
    ui->pushButton_ok_log->setText("ok");
}

// بازگشت به صفحه اصلی
void login::on_pushButton_menu_log_clicked()
{
    welcome *w = new welcome();
    w->show();
    this->close();
}
