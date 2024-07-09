#ifndef PERSON_H
#define PERSON_H

#include "job1.h"
#include <string>
#include <QSqlDatabase>

class Person {
public:
    std::string Account_ID;
    std::string First_name;
    std::string Last_name;
    std::vector<std::string> Skills;

    Person() = default;
    Person(const std::string &AccountID, const std::string &First_name, const std::string &Last_name);

    bool applyForJob(Job1 &job);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
    std::vector<std::string> getSkills() const;
    void setSkills(const std::vector<std::string> &skills);

};

#endif // PERSON_H
