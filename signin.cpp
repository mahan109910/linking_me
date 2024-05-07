#include "welcome.h"
#include "signin.h"
#include "ui_signin.h"
#include "email_number.h"
#include "welcome.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include "QSqlError"
#include "QSqlDatabase"//از این جا کتابخانه های دیتابیس
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

static int selectedLanguage = 0;

signin::signin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signin)
{
    ui->setupUi(this);
    QSqlDatabase database;//شروع کد های باز کردن دیتابیس
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("d:\\database_linking.db");
    database.open();//پایان کد های باز کردن دیتابیس

    welcome welcomeInstance; // ایجاد نمونه از کلاس welcome برای تنظیم زبان از ابتدا
    static int selectedLanguage = welcomeInstance.selectedLanguage;

    if(selectedLanguage == 1){
        ui->widget_p_signin->setStyleSheet("image: url(:/new/prefix1/image/qt_signin_p.png);");
        ui->pushButton_menu_signin->setText("صفحه اصلی");
        ui->pushButton_show_safe_signin->setText("نمایش عدد");
        ui->pushButton_ok_signin->setText("تایید");
    }else if(selectedLanguage == 2){
        ui->widget_p_signin->setStyleSheet("image: url(:/new/prefix1/image/qt_signin_e.png);");
        ui->pushButton_menu_signin->setText("menu");
        ui->pushButton_show_safe_signin->setText("show number");
        ui->pushButton_ok_signin->setText("ok");
    }

    ui->lineEdit_safe_signin->setValidator(new QIntValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_signin_name->setValidator(nameValidator);

    QRegularExpressionValidator *passwordValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_signin_password->setValidator(passwordValidator);
}

signin::~signin()
{
    delete ui;
}
//تنظیم تصاویر کد امنیتی با توجه به عدد تصادفی
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
    // Initialize the safeFrames array with pointers to the frame widgets
    safeFrames[0] = ui->frame_safe_1_signin;
    safeFrames[1] = ui->frame_safe_2_signin;
    safeFrames[2] = ui->frame_safe_3_signin;
    safeFrames[3] = ui->frame_safe_4_signin;
    generateSafeCode();
}

void signin::on_pushButton_show_safe_signin_2_clicked()
{
    // Initialize the safeFrames array with pointers to the frame widgets
    safeFrames[0] = ui->frame_safe_1_signin;
    safeFrames[1] = ui->frame_safe_2_signin;
    safeFrames[2] = ui->frame_safe_3_signin;
    safeFrames[3] = ui->frame_safe_4_signin;
    generateSafeCode();
}
//بررسی درستی عدد با عددی که کاربر وارد میکند
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
        // شرط بررسی خالی نبودن تمام اطلاعات
        if (name.isEmpty() || Password.isEmpty() || REpassword.isEmpty()) {
            if(selectedLanguage == 1){
                QMessageBox::warning(this, "خطا", "لطفا تمام فیلدها را پر کنید.");
            }else if(selectedLanguage == 2){
                QMessageBox::warning(this, ".......", ". ..............");
            }
        } else {
            // Continue with the rest of your code
            QSqlQuery q;
            q.prepare("SELECT id FROM database_linking WHERE user_name = :name");
            q.bindValue(":name", name);
            q.exec();

            if(q.first()){
                // User already exists
                if(selectedLanguage == 1){
                    QMessageBox::warning(this, "خطا", "نام کاربری قبلا استفاده شده است.");
                }else if(selectedLanguage == 2){
                    QMessageBox::warning(this, ".......", ". ..............");
                }
            } else {
                // Both are unique, continue with registration
                if (Password == REpassword) {
                    q.prepare("INSERT INTO database_linking (user_name, password) VALUES (:name, :password)");
                    q.bindValue(":name", name);
                    q.bindValue(":password", Password);
                    if (q.exec()) {
                        qDebug() << "Record inserted successfully!";
                        if(selectedLanguage == 1){
                            QMessageBox::information(this, "موفقیت", "ثبت نام با موفقیت انجام شد.");
                        }else if(selectedLanguage == 2){
                            QMessageBox::warning(this, ".......", ". ..............");
                        }
                        // Redirect to phone_number page
                        /*email_number *email_number_Page = new email_number();
                        email_number_Page->show();
                        this->hide();*///این جا اضافه شدن صفحه ی بعد
                    } else {
                        qDebug() << "Failed to insert record:" << q.lastError().text();
                    }
                } else {
                    if(selectedLanguage == 1){
                        QMessageBox::warning(this, "خطا", "رمز عبور و تکرار آن همخوانی ندارند.");
                    }else if(selectedLanguage == 2){
                        QMessageBox::warning(this, ".......", ". ..............");


                    }
                }
            }
        }
    } else {
        if(selectedLanguage == 1){
            QMessageBox::warning(this, "کد نادرست", "کد وارد شده نادرست است.");
        }else if(selectedLanguage == 2){
            QMessageBox::warning(this, ".......", ". ..............");
        }
    }
}
//انتخاب زبان فارسی
void signin::on_pushButton_Persian_signin_clicked()
{
    ui->widget_p_signin->setStyleSheet("image: url(:/new/prefix1/image/qt_signin_p.png);");
    ui->pushButton_menu_signin->setText("صفحه اصلی");
    ui->pushButton_show_safe_signin->setText("نمایش عدد");
    ui->pushButton_ok_signin->setText("تایید");
}
//انتخاب زبان انگلیسی
void signin::on_pushButton_English_signin_clicked()
{
    ui->widget_p_signin->setStyleSheet("image: url(:/new/prefix1/image/qt_signin_e.png);");
    ui->pushButton_menu_signin->setText("menu");
    ui->pushButton_show_safe_signin->setText("show number");
    ui->pushButton_ok_signin->setText("ok");
}
//رفتن به صفحه ی اصلی
void signin::on_pushButton_menu_signin_clicked()
{
    welcome *welcomePage = new welcome;
    welcomePage->show();
    this->hide();
}
