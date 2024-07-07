#ifndef POST_H
#define POST_H

#include "comment.h"
#include "like.h"
#include <iostream>
#include <vector>
#include <string>
#include <QSqlDatabase>

class Post {
public:
    std::string Post_ID;
    std::string User_ID;
    std::string Content;
    std::vector<Comment> Comments;
    std::vector<Like> Likes;

    Post(const std::string &postId, const std::string &userId, const std::string &content);
    ~Post();

    void addComment(const Comment &comment);
    void addLike(const Like &like);

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // POST_H
