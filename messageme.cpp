#include "messageme.h"
#include "ui_messageme.h"
#include "direct_message.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QUuid>

messageme::messageme(const QString &Account_ID, const QString &targetUser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::messageme), // درست کردن تعریف اشاره‌گر به ui
    Account_ID(Account_ID),
    targetUser(targetUser)
{
    ui->setupUi(this); // تنظیم رابط کاربری
    ui->labelUsername->setText(targetUser);

    connect(ui->sendButton, &QPushButton::clicked, this, &messageme::sendMessage);

    loadMessages();
}

messageme::~messageme()
{
    delete ui;
}

void messageme::sendMessage()
{
    QString messageContent = ui->textEdit->toPlainText();
    if (!messageContent.isEmpty()) {
        QString messageId = QUuid::createUuid().toString();
        QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

        Direct_Message message(messageId.toStdString(), Account_ID.toStdString(), targetUser.toStdString(),
                               messageContent.toStdString(), "text", timestamp.toStdString());
        QSqlDatabase db = QSqlDatabase::database(); // تعریف متغیر محلی QSqlDatabase
        if (message.saveToDatabase(db)) { // ارسال متغیر به تابع
            ui->listWidget->addItem(Account_ID + ": " + messageContent);
            ui->textEdit->clear();
        } else {
            qDebug() << "Error saving message to database";
        }
    }
}

void messageme::loadMessages()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT Sender_ID, Content, Content_Type FROM direct_messages WHERE (Sender_ID = ? AND Receiver_ID = ?) OR (Sender_ID = ? AND Receiver_ID = ?) ORDER BY Timestamp");
    query.addBindValue(Account_ID);
    query.addBindValue(targetUser);
    query.addBindValue(targetUser);
    query.addBindValue(Account_ID);

    if (query.exec()) {
        while (query.next()) {
            QString senderId = query.value(0).toString();
            QString content = query.value(1).toString();
            QString contentType = query.value(2).toString();

            QString messageText;
            if (contentType == "text") {
                messageText = senderId + ": " + content;
            } else if (contentType == "image") {
                messageText = senderId + ": [Image]";
            } else if (contentType == "audio") {
                messageText = senderId + ": [Audio]";
            } else if (contentType == "video") {
                messageText = senderId + ": [Video]";
            }
            ui->listWidget->addItem(messageText);
        }
    } else {
        qDebug() << "Error loading messages from database:" << query.lastError();
    }
}
