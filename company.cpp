#include "company.h"
#include "iostream"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Company::Company(const std::string &accountId, const std::string &name, int companyCode)
    : Account_ID(accountId), Name(name), Company_Code(companyCode) {
    std::cout << "Company created" << std::endl;
}

void Company::createJob(const Job1 &job) {
    Jobs.push_back(job);
}

bool Company::acceptApplicant(const std::string &jobId, const std::string &personId, QSqlDatabase& db) {
    for (auto &job : Jobs) {
        if (job.Job_ID == jobId) {
            for (auto &applicant : job.applicants) {
                if (applicant.Account_ID == personId) {
                    Employees.push_back(applicant);

                    QSqlQuery query(db);
                    query.prepare("INSERT INTO Company (Account_ID, Person_ID) VALUES (?, ?)");
                    query.addBindValue(QString::fromStdString(Account_ID));
                    query.addBindValue(QString::fromStdString(personId));
                    if (!query.exec()) {
                        qDebug() << "Error inserting into Company table:" << query.lastError();
                        return false;
                    }

                    return true;
                }
            }
        }
    }
    return false;
}

bool Company::saveToDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Company (Account_ID, company_name, company_code) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    query.addBindValue(QString::fromStdString(Name));
    query.addBindValue(Company_Code);
    if (!query.exec()) {
        qDebug() << "Error inserting into Company table:" << query.lastError();
        return false;
    }

    for (const auto& job : Jobs) {
        if (!job.saveToDatabase(db)) {
            return false;
        }
    }

    for (const auto& employee : Employees) {
        QSqlQuery empQuery(db);
        empQuery.prepare("INSERT INTO Company (Account_ID, Person_ID) VALUES (?, ?)");
        empQuery.addBindValue(QString::fromStdString(Account_ID));
        empQuery.addBindValue(QString::fromStdString(employee.Account_ID));
        if (!empQuery.exec()) {
            qDebug() << "Error inserting into Company table:" << empQuery.lastError();
            return false;
        }
    }

    return true;
}

bool Company::loadFromDatabase(const std::string& accountId, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT company_name, company_code FROM Company WHERE Account_ID = ?");
    query.addBindValue(QString::fromStdString(accountId));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading company data:" << query.lastError();
        return false;
    }
    Name = query.value(0).toString().toStdString();
    Company_Code = query.value(1).toInt();
    return true;
}

bool Company::updateInDatabase(QSqlDatabase& db) const {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Company WHERE Account_ID = ?");
    query.addBindValue(QString::fromStdString(Account_ID));
    if (!query.exec()) {
        qDebug() << "Error deleting from Company table:" << query.lastError();
        return false;
    }

    query.prepare("INSERT INTO Company (Account_ID, company_name, company_code) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Account_ID));
    query.addBindValue(QString::fromStdString(Name));
    query.addBindValue(Company_Code);
    if (!query.exec()) {
        qDebug() << "Error inserting into Company table:" << query.lastError();
        return false;
    }
    return true;
}
