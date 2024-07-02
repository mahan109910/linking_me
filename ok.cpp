#include "ok.h"
#include "ui_ok.h"

ok::ok(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ok)
{
    ui->setupUi(this);
}

ok::~ok()
{
    delete ui;
}
