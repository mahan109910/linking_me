#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Comment {
public:
    std::string Comment_ID;
    std::string User_ID;
    std::string Post_ID;
    std::string Content;

    Comment() = default; // سازنده پیش‌فرض
    Comment(const std::string &commentId, const std::string &userId, const std::string &postId, const std::string &content);

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // COMMENT_H
