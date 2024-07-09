#include "full_information.h"
#include "ui_full_information.h"
#include "home.h"
#include "welcome.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPixmap>
#include <QBitmap>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>

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
    // Redirect to company registration page
}

void full_information::on_pushButton_ok_clicked()
{
    if (saveUserData()) {
        QMessageBox::information(this, "Success", "User data saved successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save user data.");
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
    QSqlQuery query(db);
    query.prepare("SELECT Email, Phone_number, Profile_Picture FROM Account WHERE Account_ID = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.first()) {
        ui->emailLineEdit->setText(query.value(0).toString());
        ui->phoneLineEdit->setText(query.value(1).toString());

        QByteArray imageData = query.value(2).toByteArray();
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            ui->label_photo->setPixmap(pixmap);
        }
    } else {
        qDebug() << "Failed to load user data:" << query.lastError();
    }

    query.prepare("SELECT First_name, Last_name FROM Person WHERE Account_ID = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.first()) {
        ui->lineEdit_name->setText(query.value(0).toString());
        ui->lineEdit_last_name->setText(query.value(1).toString());
    } else {
        qDebug() << "Failed to load person data:" << query.lastError();
    }

    query.prepare("SELECT Skill FROM PersonSkills WHERE Account_ID = :username");
    query.bindValue(":username", username);

    if (query.exec()) {
        while (query.next()) {
            skillsList.append(query.value(0).toString());
        }
        updateSkillsDisplay();
    } else {
        qDebug() << "Failed to load skills:" << query.lastError();
    }
}

bool full_information::saveUserData()
{
    QSqlQuery query(db);

    // Update Account table
    query.prepare("UPDATE Account SET Email = :email, Phone_number = :phone, Profile_Picture = :picture WHERE Account_ID = :username");
    query.bindValue(":email", ui->emailLineEdit->text());
    query.bindValue(":phone", ui->phoneLineEdit->text());
    query.bindValue(":picture", profilePicture);
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to update Account table:" << query.lastError();
        return false;
    }

    // Update Person table
    query.prepare("UPDATE Person SET First_name = :firstName, Last_name = :lastName WHERE Account_ID = :username");
    query.bindValue(":firstName", ui->lineEdit_name->text());
    query.bindValue(":lastName", ui->lineEdit_last_name->text());
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to update Person table:" << query.lastError();
        return false;
    }

    // Delete existing skills
    query.prepare("DELETE FROM PersonSkills WHERE Account_ID = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qDebug() << "Failed to delete old skills:" << query.lastError();
        return false;
    }

    // Insert new skills
    foreach (const QString &skill, skillsList) {
        query.prepare("INSERT INTO PersonSkills (Account_ID, Skill) VALUES (:username, :skill)");
        query.bindValue(":username", username);
        query.bindValue(":skill", skill);

        if (!query.exec()) {
            qDebug() << "Failed to insert new skills:" << query.lastError();
            return false;
        }
    }

    return true;
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

