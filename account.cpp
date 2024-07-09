#include "account.h"
#include "post.h"
#include "direct_message.h"
#include <sstream>
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Account::Account(const std::string &id, const std::string &phone, const std::string &email, const std::string &password)
    : Account_ID(id), Phone_number(phone), Email(email), Password(password) {
    std::cout << "Account created" << std::endl;
}

Account::~Account() {
    std::cout << "Account destroyed" << std::endl;
}

void Account::addConnection(const std::string &id) {
    Connection.push_back(id);
}

void Account::addFollowing(const std::string &id) {
    following.push_back(id);
}

void Account::addDM(const Direct_Message &message) {
    DM.push_back(message);
}

void Account::addPost(const Post &post) {
    Posts.push_back(post);
}

bool Account::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO Account (Account_ID, Phone_number, Email, Password, Profile_Picture) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    query.addBindValue(QString::fromStdString(Phone_number));
    query.addBindValue(QString::fromStdString(Email));
    query.addBindValue(QString::fromStdString(Password));
    query.addBindValue(QByteArray::fromStdString(Profile_Picture));
    if (!query.exec()) {
        qDebug() << "Error inserting into Account table:" << query.lastError();
        return false;
    }

    // Save connections
    for (const auto& conn : Connection) {
        QSqlQuery connQuery(db);
        connQuery.prepare("INSERT INTO connections (Account_ID, Connection_ID) VALUES (?, ?)");
        connQuery.addBindValue(QString::fromStdString(Account_ID));
        connQuery.addBindValue(QString::fromStdString(conn));
        if (!connQuery.exec()) {
            qDebug() << "Error inserting into connections table:" << connQuery.lastError();
            return false;
        }
    }

    // Save followings
    for (const auto& follow : following) {
        QSqlQuery followQuery(db);
        followQuery.prepare("INSERT INTO followings (Account_ID, Following_ID) VALUES (?, ?)");
        followQuery.addBindValue(QString::fromStdString(Account_ID));
        followQuery.addBindValue(QString::fromStdString(follow));
        if (!followQuery.exec()) {
            qDebug() << "Error inserting into followings table:" << followQuery.lastError();
            return false;
        }
    }

    // Save DMs
    for (const auto& dm : DM) {
        if (!dm.saveToDatabase(db)) {
            qDebug() << "Error saving DM to database";
            return false;
        }
    }

    // Save posts
    for (const auto& post : Posts) {
        if (!post.saveToDatabase(db)) {
            qDebug() << "Error saving post to database";
            return false;
        }
    }

    return true;
}

bool Account::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Account_ID, Phone_number, Email, Password, Profile_Picture FROM Account WHERE Account_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from Account table:" << query.lastError();
        return false;
    }
    Account_ID = query.value(0).toString().toStdString();
    Phone_number = query.value(1).toString().toStdString();
    Email = query.value(2).toString().toStdString();
    Password = query.value(3).toString().toStdString(); // تبدیل به std::string
    Profile_Picture = query.value(4).toByteArray().toStdString();
    return true;
}

std::string Account::getProfilePicture() const {
    return Profile_Picture;
}

void Account::setProfilePicture(const std::string &picture) {
    Profile_Picture = picture;
}
