#include "login.h"
#include "ui_login.h"
#include "welcome.h"
#include "singin.h"
#include "managers.h"
#include "Completion_information.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
//inchude database
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QTableView> // Include QTableView header
#include <QVBoxLayout>  // Include QVBoxLayout header

LogIn::LogIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("d:\\database_linking.db");
    database.open();


}

LogIn::~LogIn()
{
    delete ui;
}

//Display the security code
void LogIn::on_pushButton_show_safe_l_clicked()
{
    ui->lineEdit_log_Password->setValidator(new QIntValidator());
    // Initialize the safeFrames array with pointers to the frame widgets
    safeFrames_l[0] = ui->frame_safe_1l;
    safeFrames_l[1] = ui->frame_safe_2l;
    safeFrames_l[2] = ui->frame_safe_3l;
    safeFrames_l[3] = ui->frame_safe_4l;
    generateSafeCode();
}

void LogIn::setSafeImage(QFrame* frame, int value) {
    QString imagePath = QString(":/new/prefix1/image/%1.png").arg(value);
    frame->setStyleSheet("image: url(" + imagePath + ");");
}

void LogIn::generateSafeCode() {
    for (int i = 0; i < 4; ++i) {
        safeCode_l[i] = QRandomGenerator::global()->bounded(10);
        setSafeImage(safeFrames_l[i], safeCode_l[i]);
    }
}

void LogIn::setLanguage(int language) {
    selectedLanguage = language;
    // Set image based on selected language
    if (selectedLanguage == 1) {
        qDebug() << "Setting Persian Image";
        ui->frame_Log->setStyleSheet(":image: url(:/new/prefix1/image/qt_sing_p.png);");
    } else if (selectedLanguage == 2) {
        qDebug() << "Setting English Image";
        ui->frame_Log->setStyleSheet("image: url(:/new/prefix1/image/qt_sing_e.png);");
    } else {
        qDebug() << "Invalid Language Code: " << selectedLanguage;
    }
}

void LogIn::on_pushButton_ok_log_clicked()
{
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
    QString Password = ui->lineEdit_log_Password->text();

    if (isValid) {
        // Check if any of the fields are empty
        if (name.isEmpty() || Password.isEmpty()) {
            QMessageBox::warning(this, "خطا", "لطفا تمام فیلدها را پر کنید.");

        }else {
            // Continue with the rest of your code

            QSqlQuery q;
            q.prepare("SELECT id FROM database_linking WHERE user_name = :name");
            q.bindValue(":name", name);
            q.exec();

            if(q.first()){
                // User not found
                QMessageBox::warning(this,"ورود نا معتبر" , "ابتدا ثبت نام کنید");
            } else {
                if (Password=="1234" && name=="HA"){
                    // Open the managers page
                    managers *managersPage = new managers();
                    managersPage->show();
                    this->hide();
                }else{
                    // Open the completion_information page
                    /*Completion_information *Completion_information_Page = new Completion_information();
                    Completion_information_Page->show();
                    this->hide();*///این جا اضافه شدن صفحه ی بعد
                }
            }
        }
    } else {
        QMessageBox::warning(this, "کد نادرست", "کد وارد شده نادرست است.");
    }
}
