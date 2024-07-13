#include "serch.h"
#include "ui_serch.h"
#include "account.h"
#include "viwe_profile.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "welcome.h"
#include "home.h"

serch::serch(const QString &Account_ID, const QString &searchText, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serch)
    , Account_ID(Account_ID)
    , searchText(searchText)
{
    ui->setupUi(this);

    // تنظیمات حالت تاریک یا روشن
    if (home::isDarkMode) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");

    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");

    }

    std::vector<std::string> usernames = Account::getAllUsernames();

    QVBoxLayout *layout = new QVBoxLayout;

    for (const std::string &username : usernames) {
        QString qUsername = QString::fromStdString(username);

        // بررسی اینکه آیا نام کاربری با searchText همخوانی دارد
        if (qUsername.contains(searchText, Qt::CaseInsensitive)) {
            // ایجاد یک QPushButton برای هر نتیجه
            QPushButton *button = new QPushButton(qUsername, this);
            layout->addWidget(button); // اضافه کردن دکمه به طرح بندی عمودی

            // اضافه کردن هندلر برای هر دکمه برای پردازش کلیک های کاربر
            connect(button, &QPushButton::clicked, this, [this, qUsername]() {
                onUserSelected(qUsername);
            });
        }
    }

    ui->scrollAreaWidgetContents->setLayout(layout);
}

serch::~serch()
{
    delete ui;
}

void serch::onUserSelected(const QString &selectedUserID)
{
    qDebug() << "Selected user ID:" << selectedUserID;
    // انتقال به صفحه بعد با نام کاربری خودم و نام کاربری انتخاب شده
    viwe_profile *viwe_profilepage = new viwe_profile(Account_ID, selectedUserID);
    viwe_profilepage->show();

}
