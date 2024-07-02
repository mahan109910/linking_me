#include "my_network.h"
#include "ui_my_network.h"

My_Network::My_Network(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::My_Network)
{
    ui->setupUi(this);
}

My_Network::~My_Network()
{
    delete ui;
}
