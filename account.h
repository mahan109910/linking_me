#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "direct_message.h"
#include "post.h"
#include <iostream>
#include <vector>
#include <string>
#include <QSqlDatabase>

class Account {
public:
    std::string Account_ID;
    std::string Phone_number;
    std::string Email;
    int password;
    std::vector<std::string> Connection;
    std::vector<std::string> following;
    std::vector<Direct_Message> DM;
    std::vector<Post> Posts;
    std::string Profile_Picture;

    Account(const std::string &id, const std::string &phone, const std::string &email, int password);
    ~Account();

    void addConnection(const std::string &id);
    void addFollowing(const std::string &id);
    void addDM(const Direct_Message &message);
    void addPost(const Post &post);

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
    std::string getProfilePicture() const;
    void setProfilePicture(const std::string &picture);
};

#endif // ACCOUNT_H
