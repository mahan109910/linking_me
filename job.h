#ifndef JOB1_H
#define JOB1_H

#include <string>
#include <vector>
#include <QSqlDatabase>

class Person; // Forward declaration

class Job {
public:
    std::string Job_ID;
    std::string Job_Title;
    std::string Company_ID;
    std::string Description;
    std::vector<Person> applicants;

    Job() = default;
    Job(const std::string &jobId, const std::string &jobTitle, const std::string &companyId, const std::string &description);

    void addApplicant(const Person &person);
    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &id, QSqlDatabase& db);
};

#endif // JOB1_H
