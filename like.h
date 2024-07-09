#ifndef LIKE_H
#define LIKE_H

#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Like {
public:
    std::string Like_ID;
    std::string User_ID;
    std::string Post_ID;

    Like() = default; // سازنده پیش‌فرض
    Like(const std::string &likeId, const std::string &userId, const std::string &postId);

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // LIKE_H
