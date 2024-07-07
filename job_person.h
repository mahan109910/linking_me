#ifndef JOB_PERSON_H
#define JOB_PERSON_H

#include <QWidget>

namespace Ui {
class job_person;
}

class job_person : public QWidget
{
    Q_OBJECT

public:
    explicit job_person(const QString &username, QWidget *parent = nullptr);
    ~job_person();

private:
    Ui::job_person *ui;
    QString username;
};

#endif // JOB_PERSON_H
