#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Direct_Message;
class Post;

class Account {
public:
    Account(const std::string &id, const std::string &phone, const std::string &email, const std::string &password);
    ~Account();

    void addConnection(const std::string &id);
    void addFollowing(const std::string &id);
    void addDM(const Direct_Message &message);
    void addPost(const Post &post);

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);

    std::string getProfilePicture() const;
    void setProfilePicture(const std::string &picture);

    std::string Account_ID;
    std::string Phone_number;
    std::string Email;
    std::string Password;  // تغییر نام فیلد به Password برای مطابقت با دیتابیس
    std::string Profile_Picture;

private:
    std::vector<std::string> Connection;
    std::vector<std::string> following;
    std::vector<Direct_Message> DM;
    std::vector<Post> Posts;
};

#endif // ACCOUNT_H
