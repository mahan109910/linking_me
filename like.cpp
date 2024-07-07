#include "like.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>

Like::Like(const std::string &likeId, const std::string &userId, const std::string &postId)
    : Like_ID(likeId), User_ID(userId), Post_ID(postId) {
    std::cout << "Like created" << std::endl;
}

bool Like::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO likes (Like_ID, User_ID, Post_ID) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Like_ID));
    query.addBindValue(QString::fromStdString(User_ID));
    query.addBindValue(QString::fromStdString(Post_ID));
    if (!query.exec()) {
        qDebug() << "Error inserting into likes table:" << query.lastError();
        return false;
    }
    return true;
}

bool Like::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Like_ID, User_ID, Post_ID FROM likes WHERE Like_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from likes table:" << query.lastError();
        return false;
    }
    Like_ID = query.value(0).toString().toStdString();
    User_ID = query.value(1).toString().toStdString();
    Post_ID = query.value(2).toString().toStdString();
    return true;
}
