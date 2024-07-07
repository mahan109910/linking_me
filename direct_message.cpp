#include "direct_message.h"
#include "time1.h" // Assuming Time class is defined here

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Direct_Message::Direct_Message(const std::string &message_id, const std::string &sender_id, const std::string &to_who,
                               const Time1 &time_sent, const std::string &content_text)
    : Message_ID(message_id), Sender_ID(sender_id), To_who(to_who), time_sent(time_sent), Content_Text(content_text) {
}

bool Direct_Message::saveToDatabase(QSqlDatabase &db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO direct_messages (Message_ID, Sender_ID, To_who, Time_sent, Content_Text) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(Message_ID));
    query.addBindValue(QString::fromStdString(Sender_ID));
    query.addBindValue(QString::fromStdString(To_who));
    query.addBindValue(QString::fromStdString(time_sent.toString())); // Assuming Time class has toString() method
    query.addBindValue(QString::fromStdString(Content_Text));
    if (!query.exec()) {
        qDebug() << "Error inserting into direct_messages table:" << query.lastError();
        return false;
    }

    // Save pictures and videos
    for (const auto &pic : Content_picture) {
        QSqlQuery picQuery(db);
        picQuery.prepare("INSERT INTO content_pictures (content_id, picture) VALUES (?, ?)");
        picQuery.addBindValue(QString::fromStdString(Message_ID));
        picQuery.addBindValue(QString::fromStdString(pic));
        if (!picQuery.exec()) {
            qDebug() << "Error inserting into content_pictures table:" << picQuery.lastError();
            return false;
        }
    }

    for (const auto &vid : Content_video) {
        QSqlQuery vidQuery(db);
        vidQuery.prepare("INSERT INTO content_videos (content_id, video) VALUES (?, ?)");
        vidQuery.addBindValue(QString::fromStdString(Message_ID));
        vidQuery.addBindValue(QString::fromStdString(vid));
        if (!vidQuery.exec()) {
            qDebug() << "Error inserting into content_videos table:" << vidQuery.lastError();
            return false;
        }
    }

    return true;
}

bool Direct_Message::loadFromDatabase(const std::string &message_id, QSqlDatabase &db) {
    QSqlQuery query(db);
    query.prepare("SELECT Sender_ID, To_who, Time_sent, Content_Text FROM direct_messages WHERE Message_ID = ?");
    query.addBindValue(QString::fromStdString(message_id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from direct_messages table:" << query.lastError();
        return false;
    }
    Sender_ID = query.value(0).toString().toStdString();
    To_who = query.value(1).toString().toStdString();
    // Assuming Time class has fromString() method
    time_sent = Time1::fromString(query.value(2).toString().toStdString());
    Content_Text = query.value(3).toString().toStdString();

    // Load pictures and videos
    QSqlQuery picQuery(db);
    picQuery.prepare("SELECT picture FROM content_pictures WHERE content_id = ?");
    picQuery.addBindValue(QString::fromStdString(message_id));
    if (!picQuery.exec()) {
        qDebug() << "Error loading from content_pictures table:" << picQuery.lastError();
        return false;
    }
    while (picQuery.next()) {
        Content_picture.push_back(picQuery.value(0).toString().toStdString());
    }

    QSqlQuery vidQuery(db);
    vidQuery.prepare("SELECT video FROM content_videos WHERE content_id = ?");
    vidQuery.addBindValue(QString::fromStdString(message_id));
    if (!vidQuery.exec()) {
        qDebug() << "Error loading from content_videos table:" << vidQuery.lastError();
        return false;
    }
    while (vidQuery.next()) {
        Content_video.push_back(vidQuery.value(0).toString().toStdString());
    }

    return true;
}
