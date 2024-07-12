#include "serch.h"
#include "ui_serch.h"
#include "home.h"

static bool selectedLanguage;
static bool isDarkMode;

serch::serch(const QString &serchv,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serch)
    , serchv(serchv)
{
    ui->setupUi(this);

    if(selectedLanguage){
        ui->pushButton_viwe->setText("نمایش");
    } else {
        ui->pushButton_viwe->setText("viwe");
    }

    if(isDarkMode){

    } else {

    }
}

serch::~serch()
{
    delete ui;
}

