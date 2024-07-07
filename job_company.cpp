#include "job_company.h"
#include "ui_job_company.h"

job_company::job_company(const QString &username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::job_company),
    username(username)
{
    ui->setupUi(this);
}

job_company::~job_company()
{
    delete ui;
}
