#include "signin.h"
#include "ui_signin.h"
#include "welcome.h"
#include "home.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

static bool selectedLanguage ;

signin::signin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signin)
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

    // تنظیم رنگ متن و پس‌زمینه برای lineEdit ها
    QString lineEditStyle = "QLineEdit { background-color: white; color: black; }";
    ui->lineEdit_safe_signin->setStyleSheet(lineEditStyle);
    ui->lineEdit_signin_name->setStyleSheet(lineEditStyle);
    ui->lineEdit_signin_password->setStyleSheet(lineEditStyle);
    ui->lineEdit_signin_REpassword->setStyleSheet(lineEditStyle);

    ui->lineEdit_safe_signin->setValidator(new QIntValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_signin_name->setValidator(nameValidator);

    translateUi(welcome::selectedLanguage);
}

signin::~signin()
{
    delete ui;
}

void signin::translateUi(bool selectedLanguage){
    if (selectedLanguage == true) {
        ui->widget_p_signin->setStyleSheet("image: url(:/new/prefix1/image/qt_signin_p.png);");
        ui->pushButton_menu_signin->setText("صفحه اصلی");
        ui->pushButton_show_safe_signin->setText("نمایش عدد");
        ui->pushButton_ok_signin->setText("تایید");
    } else if (selectedLanguage == false) {
        ui->widget_p_signin->setStyleSheet("image: url(:/new/prefix1/image/qt_signin_e.png);");
        ui->pushButton_menu_signin->setText("menu");
        ui->pushButton_show_safe_signin->setText("show number");
        ui->pushButton_ok_signin->setText("ok");
    }
}

// تنظیم تصاویر کد امنیتی با توجه به عدد تصادفی
void signin::setSafeImage(QFrame* frame, int value) {
    QString imagePath = QString(":/new/prefix1/image/%1.png").arg(value);
    frame->setStyleSheet("image: url(" + imagePath + ");");
}

void signin::generateSafeCode() {
    for (int i = 0; i < 4; ++i) {
        safeCode[i] = QRandomGenerator::global()->bounded(10);
        setSafeImage(safeFrames[i], safeCode[i]);
    }
}

void signin::on_pushButton_show_safe_signin_clicked()
{
    safeFrames[0] = ui->frame_safe_1_signin;
    safeFrames[1] = ui->frame_safe_2_signin;
    safeFrames[2] = ui->frame_safe_3_signin;
    safeFrames[3] = ui->frame_safe_4_signin;
    generateSafeCode();
}

// بررسی درستی عدد با عددی که کاربر وارد می‌کند
void signin::on_pushButton_ok_signin_clicked()
{
    int key = ui->lineEdit_safe_signin->text().toInt();
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

    QString name = ui->lineEdit_signin_name->text();
    QString Password = ui->lineEdit_signin_password->text();
    QString REpassword = ui->lineEdit_signin_REpassword->text();

    if (isValid) {
        if (name.isEmpty() || Password.isEmpty() || REpassword.isEmpty()) {
            if (selectedLanguage == true) {
                QMessageBox::warning(this, "خطا", "لطفا تمام فیلدها را پر کنید.");
            } else if (selectedLanguage == false) {
                QMessageBox::warning(this, "Error", "Please fill in all fields.");
            }
        } else {
            QSqlQuery query(db);
            query.prepare("SELECT Account_ID FROM Account WHERE Account_ID = :name");
            query.bindValue(":name", name);
            query.exec();

            if (query.first()) {
                if (selectedLanguage == true) {
                    QMessageBox::warning(this, "خطا", "نام کاربری قبلا استفاده شده است.");
                } else if (selectedLanguage == false) {
                    QMessageBox::warning(this, "Error", "Username already exists.");
                }
            } else {
                if (Password == REpassword) {
                    query.prepare("INSERT INTO Account (Account_ID, password) VALUES (:name, :password)");
                    query.bindValue(":name", name);
                    query.bindValue(":password", Password.toInt());
                    if (query.exec()) {
                        qDebug() << "Record inserted successfully!";
                        if (selectedLanguage == true) {
                            QMessageBox::information(this, "موفقیت", "ثبت نام با موفقیت انجام شد.");
                        } else if (selectedLanguage == false) {
                            QMessageBox::information(this, "Success", "Registration successful.");
                        }

                        /*Person currentUser(name.toStdString(), "", "", "", "");
                        home *homePage = new home(currentUser);
                        homePage->show();
                        this->hide();*/
                    } else {
                        qDebug() << "Failed to insert record:" << query.lastError().text();
                    }
                } else {
                    if (selectedLanguage == true) {
                        QMessageBox::warning(this, "خطا", "رمز عبور و تکرار آن همخوانی ندارند.");
                    } else if (selectedLanguage == false) {
                        QMessageBox::warning(this, "Error", "Passwords do not match.");
                    }
                }
            }
        }
    } else {
        if (selectedLanguage == true) {
            QMessageBox::warning(this, "کد نادرست", "کد وارد شده نادرست است.");
        } else if (selectedLanguage == false) {
            QMessageBox::warning(this, "Error", "Invalid code.");
        }
    }
}

// انتخاب زبان فارسی
void signin::on_pushButton_Persian_signin_clicked()
{
    selectedLanguage = true;
    translateUi(selectedLanguage);
}

// انتخاب زبان انگلیسی
void signin::on_pushButton_English_signin_clicked()
{
    selectedLanguage = false;
    translateUi(selectedLanguage);
}

// بازگشت به صفحه اصلی
void signin::on_pushButton_menu_signin_clicked()
{
    welcome *w = new welcome();
    w->show();
    this->close();
}
