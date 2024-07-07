#ifndef LIKE_H
#define LIKE_H

#include <iostream>
#include <string>
#include <QSqlDatabase>

class Like {
public:
    std::string Like_ID;
    std::string Post_ID;
    std::string User_ID;

    Like(const std::string &likeId, const std::string &postId, const std::string &userId);
    ~Like();

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // LIKE_H
