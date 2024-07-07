#include "like.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Like::Like(const std::string &likeId, const std::string &postId, const std::string &userId)
    : Like_ID(likeId), Post_ID(postId), User_ID(userId) {
    std::cout << "Like created" << std::endl;
}

Like::~Like() {
    std::cout << "Like destroyed" << std::endl;
}

bool Like::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO likes (Like_ID, Post_ID, User_ID) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Like_ID));
    query.addBindValue(QString::fromStdString(Post_ID));
    query.addBindValue(QString::fromStdString(User_ID));
    if (!query.exec()) {
        qDebug() << "Error inserting into likes table:" << query.lastError();
        return false;
    }
    return true;
}

bool Like::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Like_ID, Post_ID, User_ID FROM likes WHERE Like_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from likes table:" << query.lastError();
        return false;
    }
    Like_ID = query.value(0).toString().toStdString();
    Post_ID = query.value(1).toString().toStdString();
    User_ID = query.value(2).toString().toStdString();
    return true;
}
