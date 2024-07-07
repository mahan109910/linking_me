#include "job_person.h"
#include "ui_job_person.h"

job_person::job_person(const QString &username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::job_person),
    username(username)
{
    ui->setupUi(this);
}

job_person::~job_person()
{
    delete ui;
}
