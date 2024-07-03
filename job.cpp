#include "job.h"
#include "ui_job.h"

job::job(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::job)
{
    ui->setupUi(this);
}

job::~job()
{
    delete ui;
}
