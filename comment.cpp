#include "comment.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>

Comment::Comment(const std::string &commentId, const std::string &userId, const std::string &postId, const std::string &content)
    : Comment_ID(commentId), User_ID(userId), Post_ID(postId), Content(content) {
    std::cout << "Comment created" << std::endl;
}

bool Comment::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO comments (Comment_ID, User_ID, Post_ID, Content) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(Comment_ID));
    query.addBindValue(QString::fromStdString(User_ID));
    query.addBindValue(QString::fromStdString(Post_ID));
    query.addBindValue(QString::fromStdString(Content));
    if (!query.exec()) {
        qDebug() << "Error inserting into comments table:" << query.lastError();
        return false;
    }
    return true;
}

bool Comment::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Comment_ID, User_ID, Post_ID, Content FROM comments WHERE Comment_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from comments table:" << query.lastError();
        return false;
    }
    Comment_ID = query.value(0).toString().toStdString();
    User_ID = query.value(1).toString().toStdString();
    Post_ID = query.value(2).toString().toStdString();
    Content = query.value(3).toString().toStdString();
    return true;
}
