#include "full_information.h"
#include "ui_full_information.h"
#include "home.h"
#include "account.h"  // فرض می‌کنیم فایل مربوط به کلاس Account نیز موجود است
#include "person.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPixmap>
#include <QBitmap>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>
#include <sstream>

full_information::full_information(const QString &username, QWidget *parent)
    : QWidget(parent), ui(new Ui::full_information), username(username), account(nullptr), person(nullptr)
{
    ui->setupUi(this);

    setDarkMode(home::isDarkMode);
    db = QSqlDatabase::database();
    loadUserData();
}

full_information::~full_information()
{
    delete ui;
    delete account;
    delete person;
}

void full_information::on_pushButton_persian_clicked()
{
    ui->pushButton_home->setText("خانه");
    ui->pushButton_sing_company->setText("اگر شرکت هستید از این جا ثبت نام کنید");
}

void full_information::on_pushButton_english_clicked()
{
    ui->pushButton_home->setText("Home");
    ui->pushButton_sing_company->setText("If you are a company, register here");
}

void full_information::on_pushButton_home_clicked()
{
    home *homePage = new home(username);
    homePage->show();
    this->hide();
}

void full_information::on_pushButton_dark_sun_clicked()
{
    setDarkMode(!home::isDarkMode);
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
        if (!skillsList.contains(skill)) {
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
        item->setSelected(true);
    }
}

void full_information::loadUserData()
{
    account = new Account("", "", "", 0);
    if (!account->loadFromDatabase(username.toStdString(), db)) {
        qDebug() << "Failed to load account data";
        return;
    }

    ui->emailLineEdit->setText(QString::fromStdString(account->Email));
    ui->phoneLineEdit->setText(QString::fromStdString(account->Phone_number));

    QByteArray imageData = QByteArray::fromStdString(account->getProfilePicture());
    if (!imageData.isEmpty()) {
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        ui->label_photo->setPixmap(pixmap);
    }

    person = new Person();
    if (!person->loadFromDatabase(username.toStdString(), db)) {
        qDebug() << "Failed to load person data";
        return;
    }

    ui->lineEdit_name->setText(QString::fromStdString(person->Name));
    ui->lineEdit_age->setText(QString::number(person->Age));

    // Convert vector<string> to QStringList for skills
    std::vector<std::string> skillsVector = person->getSkills();
    QStringList skillsList;
    for (const std::string &skill : skillsVector) {
        skillsList.append(QString::fromStdString(skill));
    }
    this->skillsList = skillsList;
    updateSkillsDisplay();
}

bool full_information::saveUserData()
{
    account->Email = ui->emailLineEdit->text().toStdString();
    account->Phone_number = ui->phoneLineEdit->text().toStdString();
    account->setProfilePicture(profilePicture.toStdString());

    if (!account->saveToDatabase(db)) {
        qDebug() << "Failed to save account data";
        return false;
    }

    person->Name = ui->lineEdit_name->text().toStdString();
    person->Age = ui->lineEdit_age->text().toInt();

    // Convert QStringList to vector<string> for skills
    std::vector<std::string> skillsVector;
    for (const QString &skill : skillsList) {
        skillsVector.push_back(skill.toStdString());
    }
    person->setSkills(skillsVector);

    if (!person->saveToDatabase(db)) {
        qDebug() << "Failed to save person data";
        return false;
    }

    return true;
}

void full_information::setDarkMode(bool dark)
{
    home::isDarkMode = dark;
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
        ui->horizontalFrame_4->setStyleSheet("background-color: rgb(255, 196, 54);");
        ui->pushButton_dark_sun->setStyleSheet("border-image: url(:/new/prefix1/image/sun-dark.png);");
    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");
        ui->horizontalFrame_4->setStyleSheet("background-color: rgb(252, 220, 116);");
        ui->pushButton_dark_sun->setStyleSheet("border-image: url(:/new/prefix1/image/moon-sun.png);");
    }
}
