#include "person.h"
#include "job1.h"
#include "iostream"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Person::Person(const std::string &AccountID, const std::string &First_name, const std::string &Last_name)
    : Account_ID(AccountID), First_name(First_name), Last_name(Last_name) {
    std::cout << "Person created" << std::endl;
}

bool Person::applyForJob(Job1 &job) {
    job.addApplicant(*this);
    return true;
}

bool Person::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO persons (Account_ID, First_name, Last_name) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    query.addBindValue(QString::fromStdString(First_name));
    query.addBindValue(QString::fromStdString(Last_name));
    if (!query.exec()) {
        qDebug() << "Error inserting into persons table:" << query.lastError();
        return false;
    }
    return true;
}

bool Person::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Account_ID, First_name, Last_name FROM persons WHERE Account_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from persons table:" << query.lastError();
        return false;
    }
    Account_ID = query.value(0).toString().toStdString();
    First_name = query.value(1).toString().toStdString();
    Last_name = query.value(2).toString().toStdString();
    return true;
}

std::vector<std::string> Person::getSkills() const {
    return Skills;
}

void Person::setSkills(const std::vector<std::string> &skills) {
    Skills = skills;
}
