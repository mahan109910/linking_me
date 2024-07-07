#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <string>
#include <QSqlDatabase>

class Comment {
public:
    std::string Comment_ID;
    std::string Post_ID;
    std::string User_ID;
    std::string Content;

    Comment(const std::string &commentId, const std::string &postId, const std::string &userId, const std::string &content);
    ~Comment();

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // COMMENT_H
