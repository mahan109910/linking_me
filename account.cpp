#include "account.h"
#include "post.h"
#include "direct_message.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Account::Account(const std::string &id, const std::string &phone, const std::string &email, int password)
    : Account_ID(id), Phone_number(phone), Email(email), password(password) {
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
    query.prepare("INSERT INTO accounts (Account_ID, Phone_number, Email, password) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    query.addBindValue(QString::fromStdString(Phone_number));
    query.addBindValue(QString::fromStdString(Email));
    query.addBindValue(password);
    if (!query.exec()) {
        qDebug() << "Error inserting into accounts table:" << query.lastError();
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
    query.prepare("SELECT Account_ID, Phone_number, Email, password FROM accounts WHERE Account_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from accounts table:" << query.lastError();
        return false;
    }
    Account_ID = query.value(0).toString().toStdString();
    Phone_number = query.value(1).toString().toStdString();
    Email = query.value(2).toString().toStdString();
    password = query.value(3).toInt();

    // Load connections
    QSqlQuery connQuery(db);
    connQuery.prepare("SELECT Connection_ID FROM connections WHERE Account_ID = ?");
    connQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!connQuery.exec()) {
        qDebug() << "Error loading from connections table:" << connQuery.lastError();
        return false;
    }
    while (connQuery.next()) {
        Connection.push_back(connQuery.value(0).toString().toStdString());
    }

    // Load followings
    QSqlQuery followQuery(db);
    followQuery.prepare("SELECT Following_ID FROM followings WHERE Account_ID = ?");
    followQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!followQuery.exec()) {
        qDebug() << "Error loading from followings table:" << followQuery.lastError();
        return false;
    }
    while (followQuery.next()) {
        following.push_back(followQuery.value(0).toString().toStdString());
    }

    // Load DMs
    QSqlQuery dmQuery(db);
    dmQuery.prepare("SELECT Message_ID FROM direct_messages WHERE Sender_ID = ?");
    dmQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!dmQuery.exec()) {
        qDebug() << "Error loading from direct_messages table:" << dmQuery.lastError();
        return false;
    }
    while (dmQuery.next()) {
        Direct_Message dm;
        if (dm.loadFromDatabase(dmQuery.value(0).toString().toStdString(), db)) {
            DM.push_back(dm);
        } else {
            qDebug() << "Error loading DM with ID:" << dmQuery.value(0).toString();
        }
    }

    // Load posts
    QSqlQuery postQuery(db);
    postQuery.prepare("SELECT Post_ID FROM posts WHERE Sender_ID = ?");
    postQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!postQuery.exec()) {
        qDebug() << "Error loading from posts table:" << postQuery.lastError();
        return false;
    }
    while (postQuery.next()) {
        Post post;
        if (post.loadFromDatabase(postQuery.value(0).toString().toStdString(), db)) {
            Posts.push_back(post);
        } else {
            qDebug() << "Error loading post with ID:" << postQuery.value(0).toString();
        }
    }

    return true;
}

std::string Account::getProfilePicture() const {
    return Profile_Picture;
}

void Account::setProfilePicture(const std::string &picture) {
    Profile_Picture = picture;
}
