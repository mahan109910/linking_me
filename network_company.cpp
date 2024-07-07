#include "network_company.h"
#include "ui_network_company.h"

network_company::network_company(const QString &username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::network_company),
    username(username)
{
    ui->setupUi(this);
}

network_company::~network_company()
{
    delete ui;
}
