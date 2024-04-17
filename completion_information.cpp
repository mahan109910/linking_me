#include "completion_information.h"
#include "ui_completion_information.h"

Completion_information::Completion_information(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Completion_information)
{
    ui->setupUi(this);
}

Completion_information::~Completion_information()
{
    delete ui;
}
