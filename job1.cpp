#include "job1.h"
#include "person.h"
#include "iostream"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Job1::Job1(const std::string &jobId, const std::string &jobTitle, const std::string &companyId, const std::string &description)
    : Job_ID(jobId), Job_Title(jobTitle), Company_ID(companyId), Description(description) {
    std::cout << "Job1 created" << std::endl;
}

void Job1::addApplicant(const Person &person) {
    applicants.push_back(person);
}

bool Job1::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO jobs (Job_ID, Job_Title, Company_ID, Description) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(Job_ID));
    query.addBindValue(QString::fromStdString(Job_Title));
    query.addBindValue(QString::fromStdString(Company_ID));
    query.addBindValue(QString::fromStdString(Description));
    if (!query.exec()) {
        qDebug() << "Error inserting into jobs table:" << query.lastError();
        return false;
    }

    for (const auto& applicant : applicants) {
        QSqlQuery appQuery(db);
        appQuery.prepare("INSERT INTO job_applicants (Job_ID, Person_ID) VALUES (?, ?)");
        appQuery.addBindValue(QString::fromStdString(Job_ID));
        appQuery.addBindValue(QString::fromStdString(applicant.Person_ID));
        if (!appQuery.exec()) {
            qDebug() << "Error inserting into job_applicants table:" << appQuery.lastError();
            return false;
        }
    }

    return true;
}

bool Job1::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Job_ID, Job_Title, Company_ID, Description FROM jobs WHERE Job_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from jobs table:" << query.lastError();
        return false;
    }
    Job_ID = query.value(0).toString().toStdString();
    Job_Title = query.value(1).toString().toStdString();
    Company_ID = query.value(2).toString().toStdString();
    Description = query.value(3).toString().toStdString();

    QSqlQuery appQuery(db);
    appQuery.prepare("SELECT Person_ID FROM job_applicants WHERE Job_ID = ?");
    appQuery.addBindValue(QString::fromStdString(Job_ID));
    if (!appQuery.exec()) {
        qDebug() << "Error loading from job_applicants table:" << appQuery.lastError();
        return false;
    }
    while (appQuery.next()) {
        Person person;
        if (person.loadFromDatabase(appQuery.value(0).toString().toStdString(), db)) {
            applicants.push_back(person);
        } else {
            qDebug() << "Error loading applicant with ID:" << appQuery.value(0).toString();
        }
    }

    return true;
}
