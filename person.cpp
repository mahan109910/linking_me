#include "person.h"
#include "job1.h"
#include "iostream"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Person::Person(const std::string &personId, const std::string &name, int age)
    : Person_ID(personId), Name(name), Age(age) {
    std::cout << "Person created" << std::endl;
}

bool Person::applyForJob(Job1 &job) {
    job.addApplicant(*this);
    return true;
}

bool Person::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO persons (Person_ID, Name, Age) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Person_ID));
    query.addBindValue(QString::fromStdString(Name));
    query.addBindValue(Age);
    if (!query.exec()) {
        qDebug() << "Error inserting into persons table:" << query.lastError();
        return false;
    }
    return true;
}

bool Person::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Person_ID, Name, Age FROM persons WHERE Person_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from persons table:" << query.lastError();
        return false;
    }
    Person_ID = query.value(0).toString().toStdString();
    Name = query.value(1).toString().toStdString();
    Age = query.value(2).toInt();
    return true;
}
