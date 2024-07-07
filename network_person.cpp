#include "network_person.h"
#include "ui_network_person.h"

network_person::network_person(const QString &username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::network_person),
    username(username)
{
    ui->setupUi(this);
}

network_person::~network_person()
{
    delete ui;
}
