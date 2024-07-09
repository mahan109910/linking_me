#ifndef COMPANY_H
#define COMPANY_H

#include "job1.h"
#include "person.h"
#include <string>
#include <vector>
#include <QSqlDatabase>

class Company {
public:
    std::string Account_ID;
    std::string Name;
    int Company_Code;
    std::vector<Job1> Jobs;
    std::vector<Person> Employees;

    Company() = default;
    Company(const std::string &accountId, const std::string &name, int companyCode);

    void createJob(const Job1 &job);
    bool acceptApplicant(const std::string &jobId, const std::string &personId, QSqlDatabase& db);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &accountId, QSqlDatabase& db);
};

#endif // COMPANY_H
