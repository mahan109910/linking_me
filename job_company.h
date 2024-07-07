#ifndef JOB_COMPANY_H
#define JOB_COMPANY_H

#include <QWidget>

namespace Ui {
class job_company;
}

class job_company : public QWidget
{
    Q_OBJECT

public:
    explicit job_company(const QString &username, QWidget *parent = nullptr);
    ~job_company();

private:
    Ui::job_company *ui;
    QString username;
};

#endif // JOB_COMPANY_H
