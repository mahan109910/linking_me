#ifndef PERSON_H
#define PERSON_H

#include "job1.h"
#include <string>
#include <QSqlDatabase>

class Person {
public:
    std::string Person_ID;
    std::string Name;
    int Age;

    Person() = default;
    Person(const std::string &personId, const std::string &name, int age);

    bool applyForJob(Job1 &job);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // PERSON_H
