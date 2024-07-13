#include "message.h"
#include "ui_message.h"
#include "messageme.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QListWidgetItem>
#include <QDebug>

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
    this->hide();
}
