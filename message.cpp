#include "message.h"
#include "ui_message.h"
#include "messageme.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QListWidgetItem>
#include <QDebug>
#include "home.h"
#include "job_person.h"
#include "job_company.h"
#include "network_company.h"
#include "network_person.h"

message::message(const QString &Account_ID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message),
    Account_ID(Account_ID)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &message::openChat);

    // بارگذاری لیست کاربران
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT DISTINCT Sender_ID, Receiver_ID FROM direct_messages WHERE Sender_ID = ? OR Receiver_ID = ?");
    query.addBindValue(Account_ID);
    query.addBindValue(Account_ID);

    if (query.exec()) {
        while (query.next()) {
            QString user1 = query.value(0).toString();
            QString user2 = query.value(1).toString();
            if (user1 != Account_ID) {
                ui->listWidget->addItem(user1);
            } else if (user2 != Account_ID) {
                ui->listWidget->addItem(user2);
            }
        }
    } else {
        qDebug() << "Error loading users from direct_messages table:" << query.lastError();
    }
}

message::~message()
{
    delete ui;
}

void message::openChat(QListWidgetItem *item)
{
    QString selectedUser = item->text();
    messageme *chatPage = new messageme(Account_ID, selectedUser);
    chatPage->show();
}


void message::on_pushButton_home_home_clicked()
{
    home *homePage = new home(Account_ID);
    homePage->show();
    this->hide();
}

void message::on_pushButton_job_home_clicked()
{
    if (isCompany) {
        job_company *jobPage = new job_company(Account_ID);
        jobPage->show();
    } else {
        job_person *jobPage = new job_person(Account_ID);
        jobPage->show();
    }
    this->hide();
}

void message::on_pushButton_network_home_clicked()
{
    if (isCompany) {
        network_company *network_companyPage = new network_company(Account_ID);
        network_companyPage->show();
    } else {
        network_person *network_personPage = new network_person(Account_ID);
        network_personPage->show();
    }
    this->hide();
}

