#include "person.h"
#include "job1.h"
#include "iostream"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Person::Person() {
    std::cout << "Default Person created" << std::endl;
}

Person::Person(const std::string &AccountID, const std::string &First_name, const std::string &Last_name)
    : Account_ID(AccountID), First_name(First_name), Last_name(Last_name) {
    std::cout << "Person created" << std::endl;
}

Person::Person(const Person &other)
    : Account_ID(other.Account_ID), First_name(other.First_name), Last_name(other.Last_name), Skills(other.Skills), SearchHistory(other.SearchHistory) {
    std::cout << "Person copied" << std::endl;
}

bool Person::applyForJob(Job1 &job) {
    job.addApplicant(*this);
    return true;
}

bool Person::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO Person (Account_ID, First_name, Last_name) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    query.addBindValue(QString::fromStdString(First_name));
    query.addBindValue(QString::fromStdString(Last_name));
    if (!query.exec()) {
        qDebug() << "Error inserting into Person table:" << query.lastError();
        return false;
    }

    // Delete existing skills
    QSqlQuery deleteSkillsQuery(db);
    deleteSkillsQuery.prepare("DELETE FROM PersonSkills WHERE Account_ID = ?");
    deleteSkillsQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!deleteSkillsQuery.exec()) {
        qDebug() << "Error deleting existing skills:" << deleteSkillsQuery.lastError();
        return false;
    }

    // Save new skills
    for (const auto& skill : Skills) {
        QSqlQuery skillQuery(db);
        skillQuery.prepare("INSERT INTO PersonSkills (Account_ID, Skill) VALUES (?, ?)");
        skillQuery.addBindValue(QString::fromStdString(Account_ID));
        skillQuery.addBindValue(QString::fromStdString(skill));
        if (!skillQuery.exec()) {
            qDebug() << "Error inserting into PersonSkills table:" << skillQuery.lastError();
            return false;
        }
    }

    return true;
}

bool Person::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Account_ID, First_name, Last_name FROM Person WHERE Account_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from Person table:" << query.lastError();
        return false;
    }
    Account_ID = query.value(0).toString().toStdString();
    First_name = query.value(1).toString().toStdString();
    Last_name = query.value(2).toString().toStdString();

    // Load skills
    QSqlQuery skillQuery(db);
    skillQuery.prepare("SELECT Skill FROM PersonSkills WHERE Account_ID = ?");
    skillQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!skillQuery.exec()) {
        qDebug() << "Error loading from PersonSkills table:" << skillQuery.lastError();
        return false;
    }

    Skills.clear();
    while (skillQuery.next()) {
        Skills.push_back(skillQuery.value(0).toString().toStdString());
    }

    // Load search history
    QSqlQuery searchQuery(db);
    searchQuery.prepare("SELECT \"1\", \"2\", \"3\", \"4\", \"5\" FROM serch WHERE Account = ?");
    searchQuery.addBindValue(QString::fromStdString(Account_ID));
    if (!searchQuery.exec()) {
        qDebug() << "Error loading from serch table:" << searchQuery.lastError();
        return false;
    }

    SearchHistory.clear();
    if (searchQuery.next()) {
        for (int i = 0; i < 5; ++i) {
            QString search = searchQuery.value(i).toString();
            if (!search.isEmpty()) {
                SearchHistory.push_back(search.toStdString());
            }
        }
    }

    return true;
}

std::vector<std::string> Person::getSkills() const {
    return Skills;
}

void Person::setSkills(const std::vector<std::string> &skills) {
    Skills = skills;
}

bool Person::updateSearchHistory(const std::string &newSearch, QSqlDatabase& db) {
    QSqlQuery query(db);

    // Load current search history
    if (!loadFromDatabase(Account_ID, db)) {
        return false;
    }

    // Update search history
    SearchHistory.insert(SearchHistory.begin(), newSearch);
    if (SearchHistory.size() > 5) {
        SearchHistory.pop_back();
    }

    // Save updated search history to database
    query.prepare("INSERT OR REPLACE INTO serch (Account, \"1\", \"2\", \"3\", \"4\", \"5\") VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    for (int i = 0; i < 5; ++i) {
        if (i < SearchHistory.size()) {
            query.addBindValue(QString::fromStdString(SearchHistory[i]));
        } else {
            query.addBindValue(QVariant(QVariant::String));
        }
    }

    if (!query.exec()) {
        qDebug() << "Error updating serch table:" << query.lastError();
        return false;
    }

    return true;
}
