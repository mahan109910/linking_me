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
//inchude database
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

//extern int selectedLanguage ;
singIn::singIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::singIn)
{
    ui->setupUi(this);
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("d:\\database_linking.db");
    database.open();

    ui->lineEdit_safe_sing->setValidator(new QIntValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_sing_name->setValidator(nameValidator);

    QRegularExpressionValidator *passwordValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"));
    ui->lineEdit_sing_password->setValidator(passwordValidator);
    qDebug() << selectedLanguage;
    // Initialize selectedLanguage to 0 (default)
   // selectedLanguage = 0;
}

singIn::~singIn()
{
    delete ui;
}

void singIn::setSafeImage(QFrame* frame, int value) {
    QString imagePath = QString(":/new/prefix1/image/%1.png").arg(value);
    frame->setStyleSheet("image: url(" + imagePath + ");");
}

void singIn::generateSafeCode() {
    for (int i = 0; i < 4; ++i) {
        safeCode[i] = QRandomGenerator::global()->bounded(10);
        setSafeImage(safeFrames[i], safeCode[i]);
    }
}

void singIn::setLanguage(int language) {
    selectedLanguage = language;
    // Set image based on selected language
    if (selectedLanguage == 1) {
        qDebug() << "Setting Persian Image";
        ui->widget_p_sing->setStyleSheet(":image: url(:/new/prefix1/image/qt_sing_p.png);");
    } else if (selectedLanguage == 2) {
        qDebug() << "Setting English Image";
        ui->widget_p_sing->setStyleSheet("image: url(:/new/prefix1/image/qt_sing_e.png);");
    } else {
        qDebug() << "Invalid Language Code: " << selectedLanguage;
    }
}

void singIn::on_pushButton_show_safe_clicked()
{
    // Initialize the safeFrames array with pointers to the frame widgets
    safeFrames[0] = ui->frame_safe_1_sign;
    safeFrames[1] = ui->frame_safe_2_sign;
    safeFrames[2] = ui->frame_safe_3_sign;
    safeFrames[3] = ui->frame_safe_4_sign;
    generateSafeCode();
}

void singIn::on_pushButton_ok_sing_clicked()
{
    int key = ui->lineEdit_safe_sing->text().toInt();

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

    QString name = ui->lineEdit_sing_name->text();
    QString Password = ui->lineEdit_sing_password->text();
    QString REpassword = ui->lineEdit_sing_REpassword->text();

    if (isValid) {
        // Check if any of the fields are empty
        if (name.isEmpty() || Password.isEmpty() || REpassword.isEmpty()) {
            QMessageBox::warning(this, "خطا", "لطفا تمام فیلدها را پر کنید.");
        } else {
            // Continue with the rest of your code
            QSqlQuery q;
            q.prepare("SELECT id FROM database_linking WHERE user_name = :name");
            q.bindValue(":name", name);
            q.exec();

            if(q.first()){
                // User already exists
                QMessageBox::warning(this, "خطا", "نام کاربری قبلا استفاده شده است.");
            } else {
                // Both are unique, continue with registration
                if (Password == REpassword) {
                    q.prepare("INSERT INTO database_linking (user_name, password) VALUES (:name, :password)");
                    q.bindValue(":name", name);
                    q.bindValue(":password", Password);
                    if (q.exec()) {
                        qDebug() << "Record inserted successfully!";
                        QMessageBox::information(this, "موفقیت", "ثبت نام با موفقیت انجام شد.");
                        // Redirect to phone_number page
                        /*email_number *email_number_Page = new email_number();
                        email_number_Page->show();
                        this->hide();*///این جا اضافه شدن صفحه ی بعد
                    } else {
                        qDebug() << "Failed to insert record:" << q.lastError().text();
                    }
                } else {
                    QMessageBox::warning(this, "خطا", "رمز عبور و تکرار آن همخوانی ندارند.");
                }
            }
        }
    } else {
        QMessageBox::warning(this, "کد نادرست", "کد وارد شده نادرست است.");
    }
}
