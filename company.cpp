#include "company.h"
#include "iostream"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Company::Company(const std::string &companyId, const std::string &name, const std::string &industry)
    : Company_ID(companyId), Name(name), Industry(industry) {
    std::cout << "Company created" << std::endl;
}

void Company::createJob(const Job1 &job) {
    Jobs.push_back(job);
}

bool Company::acceptApplicant(const std::string &jobId, const std::string &personId, QSqlDatabase& db) {
    for (auto &job : Jobs) {
        if (job.Job_ID == jobId) {
            for (auto &applicant : job.applicants) {
                if (applicant.Person_ID == personId) {
                    Employees.push_back(applicant);

                    QSqlQuery query(db);
                    query.prepare("INSERT INTO company_employees (Company_ID, Person_ID) VALUES (?, ?)");
                    query.addBindValue(QString::fromStdString(Company_ID));
                    query.addBindValue(QString::fromStdString(personId));
                    if (!query.exec()) {
                        qDebug() << "Error inserting into company_employees table:" << query.lastError();
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
    query.prepare("INSERT INTO companies (Company_ID, Name, Industry) VALUES (?, ?, ?)");
    query.addBindValue(QString::fromStdString(Company_ID));
    query.addBindValue(QString::fromStdString(Name));
    query.addBindValue(QString::fromStdString(Industry));
    if (!query.exec()) {
        qDebug() << "Error inserting into companies table:" << query.lastError();
        return false;
    }

    for (const auto& job : Jobs) {
        if (!job.saveToDatabase(db)) {
            return false;
        }
    }

    for (const auto& employee : Employees) {
        QSqlQuery empQuery(db);
        empQuery.prepare("INSERT INTO company_employees (Company_ID, Person_ID) VALUES (?, ?)");
        empQuery.addBindValue(QString::fromStdString(Company_ID));
        empQuery.addBindValue(QString::fromStdString(employee.Person_ID));
        if (!empQuery.exec()) {
            qDebug() << "Error inserting into company_employees table:" << empQuery.lastError();
            return false;
        }
    }

    return true;
}

bool Company::loadFromDatabase(const std::string &id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT Company_ID, Name, Industry FROM companies WHERE Company_ID = ?");
    query.addBindValue(QString::fromStdString(id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from companies table:" << query.lastError();
        return false;
    }
    Company_ID = query.value(0).toString().toStdString();
    Name = query.value(1).toString().toStdString();
    Industry = query.value(2).toString().toStdString();

    QSqlQuery jobQuery(db);
    jobQuery.prepare("SELECT Job_ID FROM jobs WHERE Company_ID = ?");
    jobQuery.addBindValue(QString::fromStdString(Company_ID));
    if (!jobQuery.exec()) {
        qDebug() << "Error loading from jobs table:" << jobQuery.lastError();
        return false;
    }
    while (jobQuery.next()) {
        Job1 job(jobQuery.value(0).toString().toStdString(), "", "", "");
        if (job.loadFromDatabase(jobQuery.value(0).toString().toStdString(), db)) {
            Jobs.push_back(job);
        } else {
            qDebug() << "Error loading job with ID:" << jobQuery.value(0).toString();
        }
    }

    QSqlQuery empQuery(db);
    empQuery.prepare("SELECT Person_ID FROM company_employees WHERE Company_ID = ?");
    empQuery.addBindValue(QString::fromStdString(Company_ID));
    if (!empQuery.exec()) {
        qDebug() << "Error loading from company_employees table:" << empQuery.lastError();
        return false;
    }
    while (empQuery.next()) {
        Person person;
        if (person.loadFromDatabase(empQuery.value(0).toString().toStdString(), db)) {
            Employees.push_back(person);
        } else {
            qDebug() << "Error loading employee with ID:" << empQuery.value(0).toString();
        }
    }

    return true;
}
