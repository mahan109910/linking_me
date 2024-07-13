#ifndef COMPANY_H
#define COMPANY_H

#include "job.h"
#include "person.h"
#include <string>
#include <vector>
#include <QSqlDatabase>

class Company {
public:
    std::string Account_ID;
    std::string Name;
    int Company_Code;
    std::vector<Job> Jobs;
    std::vector<Person> Employees;

    Company() = default;
    Company(const std::string &accountId, const std::string &name, int companyCode);

    void createJob(const Job &job);
    bool acceptApplicant(const std::string &jobId, const std::string &personId, QSqlDatabase& db);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string& accountId, QSqlDatabase& db);
    bool updateInDatabase(QSqlDatabase& db) const;
};

#endif // COMPANY_H
