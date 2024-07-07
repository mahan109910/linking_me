#include "direct_message.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

bool Direct_Message::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO direct_messages (Message_ID, Sender_ID, Receiver_ID, Content, Timestamp) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(message_id));
    query.addBindValue(QString::fromStdString(sender_id));
    query.addBindValue(QString::fromStdString(receiver_id));
    query.addBindValue(QString::fromStdString(content));
    query.addBindValue(QString::fromStdString(timestamp));
    if (!query.exec()) {
        qDebug() << "Error inserting into direct_messages table:" << query.lastError();
        return false;
    }
    return true;
}

bool Direct_Message::loadFromDatabase(const std::string &msg_id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Message_ID, Sender_ID, Receiver_ID, Content, Timestamp FROM direct_messages WHERE Message_ID = ?");
    query.addBindValue(QString::fromStdString(msg_id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from direct_messages table:" << query.lastError();
        return false;
    }
    message_id = query.value(0).toString().toStdString();
    sender_id = query.value(1).toString().toStdString();
    receiver_id = query.value(2).toString().toStdString();
    content = query.value(3).toString().toStdString();
    timestamp = query.value(4).toString().toStdString();
    return true;
}
