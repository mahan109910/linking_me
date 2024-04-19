#include "email_number.h"
#include "ui_email_number.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include <QSqlError>
//inchude database
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>


email_number::email_number(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::email_number)
{
    ui->setupUi(this);
}

// اضافه کردن destructor در صورتی که در header تعریف شده است
email_number::~email_number() {
    delete ui;
}

