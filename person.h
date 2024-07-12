#ifndef PERSON_H
#define PERSON_H

#include "job1.h"
#include <string>
#include <QSqlDatabase>
#include <vector>

class Person {
public:
    Person();  // سازنده پیش‌فرض
    Person(const std::string &Account_ID, const std::string &First_name, const std::string &Last_name);
    Person(const Person &other);

    std::string Account_ID;
    std::string First_name;
    std::string Last_name;
    std::vector<std::string> Skills;
    std::vector<std::string> SearchHistory;

    bool applyForJob(Job1 &job);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
    std::vector<std::string> getSkills() const;
    void setSkills(const std::vector<std::string> &skills);
    bool updateSearchHistory(const std::string &newSearch, QSqlDatabase& db);
};

#endif // PERSON_H
