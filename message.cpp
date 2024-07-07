#include "message.h"
#include "ui_message.h"

message::message(const QString &username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message),
    username(username)
{
    ui->setupUi(this);
}

message::~message()
{
    delete ui;
}
