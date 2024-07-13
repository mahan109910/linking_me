#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <QSqlDatabase>
#include "post.h"
#include "direct_message.h"

class Account {
public:
    // سازنده جدید با 5 پارامتر
    Account(const std::string &id, const std::string &phone, const std::string &email, const std::string &password/*, const std::string &bio*/);

    // سازنده بدون پارامتر
    Account();

    // مخرب
    ~Account();

    static std::vector<std::string> getAllUsernames();

    // متغیرها
    std::string Account_ID;
    std::string Phone_number;
    std::string Email;
    std::string Password;
    //std::string Bio;
    std::string Profile_Picture;

    // متدها
    void addConnection(const std::string &id);
    void addFollowing(const std::string &id);
    void addDM(const Direct_Message &message);
    void addPost(const Post &post);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);

    std::string getProfilePicture() const;
    void setProfilePicture(const std::string &picture);
    //std::string getBio() const;
    //void setBio(const std::string &bio);

    std::string getAccountID() const;



private:
    std::vector<std::string> Connection;
    std::vector<std::string> following;
    std::vector<Direct_Message> DM;
    std::vector<Post> Posts;
};

#endif // ACCOUNT_H
