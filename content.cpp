#include "content.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

bool Content::saveToDatabase(const std::string &content_id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO contents (content_id, sender_ID, Content_Text) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(content_id));
    query.addBindValue(QString::fromStdString(sender_ID));
    query.addBindValue(QString::fromStdString(Content_Text));
    if (!query.exec()) {
        qDebug() << "Error inserting into contents table:" << query.lastError();
        return false;
    }

    if (!time_sent.saveToDatabase(content_id, db)) {
        return false;
    }

    for (const auto& pic : Content_picture) {
        QSqlQuery picQuery(db);
        picQuery.prepare("INSERT INTO content_pictures (content_id, picture) VALUES (?, ?)");
        picQuery.addBindValue(QString::fromStdString(content_id));
        picQuery.addBindValue(QString::fromStdString(pic));
        if (!picQuery.exec()) {
            qDebug() << "Error inserting into content_pictures table:" << picQuery.lastError();
            return false;
        }
    }

    for (const auto& vid : Content_video) {
        QSqlQuery vidQuery(db);
        vidQuery.prepare("INSERT INTO content_videos (content_id, video) VALUES (?, ?)");
        vidQuery.addBindValue(QString::fromStdString(content_id));
        vidQuery.addBindValue(QString::fromStdString(vid));
        if (!vidQuery.exec()) {
            qDebug() << "Error inserting into content_videos table:" << vidQuery.lastError();
            return false;
        }
    }

    return true;
}

bool Content::loadFromDatabase(const std::string &content_id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT sender_ID, Content_Text FROM contents WHERE content_id = ?");
    query.addBindValue(QString::fromStdString(content_id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from contents table:" << query.lastError();
        return false;
    }
    sender_ID = query.value(0).toString().toStdString();
    Content_Text = query.value(1).toString().toStdString();

    if (!time_sent.loadFromDatabase(content_id, db)) {
        return false;
    }

    QSqlQuery picQuery(db);
    picQuery.prepare("SELECT picture FROM content_pictures WHERE content_id = ?");
    picQuery.addBindValue(QString::fromStdString(content_id));
    if (!picQuery.exec()) {
        qDebug() << "Error loading from content_pictures table:" << picQuery.lastError();
        return false;
    }
    while (picQuery.next()) {
        Content_picture.push_back(picQuery.value(0).toString().toStdString());
    }

    QSqlQuery vidQuery(db);
    vidQuery.prepare("SELECT video FROM content_videos WHERE content_id = ?");
    vidQuery.addBindValue(QString::fromStdString(content_id));
    if (!vidQuery.exec()) {
        qDebug() << "Error loading from content_videos table:" << vidQuery.lastError();
        return false;
    }
    while (vidQuery.next()) {
        Content_video.push_back(vidQuery.value(0).toString().toStdString());
    }

    return true;
}
