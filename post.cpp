#include "post.h"
#include "comment.h"
#include "like.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>

Post::Post(const std::string &postId, const std::string &userId, const std::string &content)
    : Post_ID(postId), User_ID(userId), Content(content) {
    std::cout << "Post created" << std::endl;
}

Post::~Post() {
    std::cout << "Post destroyed" << std::endl;
}

void Post::addComment(const Comment &comment) {
    Comments.push_back(comment);
}

void Post::addLike(const Like &like) {
    Likes.push_back(like);
}

bool Post::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO posts (Post_ID, User_ID, Content) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Post_ID));
    query.addBindValue(QString::fromStdString(User_ID));
    query.addBindValue(QString::fromStdString(Content));
    if (!query.exec()) {
        qDebug() << "Error inserting into posts table:" << query.lastError();
        return false;
    }

    // Save comments
    for (const auto& comment : Comments) {
        if (!comment.saveToDatabase(db)) {
            qDebug() << "Error saving comment to database";
            return false;
        }
    }

    // Save likes
    for (const auto& like : Likes) {
        if (!like.saveToDatabase(db)) {
            qDebug() << "Error saving like to database";
            return false;
        }
    }

    return true;
}

bool Post::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Post_ID, User_ID, Content FROM posts WHERE Post_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from posts table:" << query.lastError();
        return false;
    }
    Post_ID = query.value(0).toString().toStdString();
    User_ID = query.value(1).toString().toStdString();
    Content = query.value(2).toString().toStdString();

    // Load comments
    QSqlQuery commentQuery(db);
    commentQuery.prepare("SELECT Comment_ID FROM comments WHERE Post_ID = ?");
    commentQuery.addBindValue(QString::fromStdString(Post_ID));
    if (!commentQuery.exec()) {
        qDebug() << "Error loading from comments table:" << commentQuery.lastError();
        return false;
    }
    while (commentQuery.next()) {
        Comment comment;
        if (comment.loadFromDatabase(commentQuery.value(0).toString().toStdString(), db)) {
            Comments.push_back(comment);
        } else {
            qDebug() << "Error loading comment with ID:" << commentQuery.value(0).toString();
        }
    }

    // Load likes
    QSqlQuery likeQuery(db);
    likeQuery.prepare("SELECT Like_ID FROM likes WHERE Post_ID = ?");
    likeQuery.addBindValue(QString::fromStdString(Post_ID));
    if (!likeQuery.exec()) {
        qDebug() << "Error loading from likes table:" << likeQuery.lastError();
        return false;
    }
    while (likeQuery.next()) {
        Like like;
        if (like.loadFromDatabase(likeQuery.value(0).toString().toStdString(), db)) {
            Likes.push_back(like);
        } else {
            qDebug() << "Error loading like with ID:" << likeQuery.value(0).toString();
        }
    }

    return true;
}
